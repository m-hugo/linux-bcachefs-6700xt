/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include <linux/firmware.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/pci.h>

#include <drm/amdgpu_drm.h>

#include "amdgpu.h"
#include "amdgpu_ih.h"
#include "amdgpu_uvd.h"
#include "amdgpu_vce.h"
#include "amdgpu_ucode.h"
#include "amdgpu_psp.h"
#include "atom.h"
#include "amd_pcie.h"

#include "uvd/uvd_7_0_offset.h"
#include "gc/gc_9_0_offset.h"
#include "gc/gc_9_0_sh_mask.h"
#include "sdma0/sdma0_4_0_offset.h"
#include "sdma1/sdma1_4_0_offset.h"
#include "nbio/nbio_7_0_default.h"
#include "nbio/nbio_7_0_offset.h"
#include "nbio/nbio_7_0_sh_mask.h"
#include "nbio/nbio_7_0_smn.h"
#include "mp/mp_9_0_offset.h"

#include "soc15.h"
#include "soc15_common.h"
#include "gfx_v9_0.h"
#include "gmc_v9_0.h"
#include "gfxhub_v1_0.h"
#include "mmhub_v1_0.h"
#include "df_v1_7.h"
#include "df_v3_6.h"
#include "nbio_v6_1.h"
#include "nbio_v7_0.h"
#include "nbio_v7_4.h"
#include "hdp_v4_0.h"
#include "vega10_ih.h"
#include "vega20_ih.h"
#include "navi10_ih.h"
#include "sdma_v4_0.h"
#include "uvd_v7_0.h"
#include "vce_v4_0.h"
#include "vcn_v1_0.h"
#include "vcn_v2_0.h"
#include "jpeg_v2_0.h"
#include "vcn_v2_5.h"
#include "jpeg_v2_5.h"
#include "smuio_v9_0.h"
#include "smuio_v11_0.h"
#include "smuio_v13_0.h"
#include "amdgpu_vkms.h"
#include "mxgpu_ai.h"
#include "amdgpu_ras.h"
#include "amdgpu_xgmi.h"
#include <uapi/linux/kfd_ioctl.h>

#define mmMP0_MISC_CGTT_CTRL0                                                                   0x01b9
#define mmMP0_MISC_CGTT_CTRL0_BASE_IDX                                                          0
#define mmMP0_MISC_LIGHT_SLEEP_CTRL                                                             0x01ba
#define mmMP0_MISC_LIGHT_SLEEP_CTRL_BASE_IDX                                                    0

/**
 * soc15_program_register_sequence - program an array of registers.
 *
 * @adev: amdgpu_device pointer
 * @regs: pointer to the register array
 * @array_size: size of the register array
 *
 * Programs an array or registers with and and or masks.
 * This is a helper for setting golden registers.
 */

void soc15_program_register_sequence(struct amdgpu_device *adev,
					     const struct soc15_reg_golden *regs,
					     const u32 array_size)
{
	const struct soc15_reg_golden *entry;
	u32 tmp, reg;
	int i;

	for (i = 0; i < array_size; ++i) {
		entry = &regs[i];
		reg =  adev->reg_offset[entry->hwip][entry->instance][entry->segment] + entry->reg;

		if (entry->and_mask == 0xffffffff) {
			tmp = entry->or_mask;
		} else {
			tmp = (entry->hwip == GC_HWIP) ?
				RREG32_SOC15_IP(GC, reg) : RREG32(reg);

			tmp &= ~(entry->and_mask);
			tmp |= (entry->or_mask & entry->and_mask);
		}

		if (reg == SOC15_REG_OFFSET(GC, 0, mmPA_SC_BINNER_EVENT_CNTL_3) ||
			reg == SOC15_REG_OFFSET(GC, 0, mmPA_SC_ENHANCE) ||
			reg == SOC15_REG_OFFSET(GC, 0, mmPA_SC_ENHANCE_1) ||
			reg == SOC15_REG_OFFSET(GC, 0, mmSH_MEM_CONFIG))
			WREG32_RLC(reg, tmp);
		else
			(entry->hwip == GC_HWIP) ?
				WREG32_SOC15_IP(GC, reg, tmp) : WREG32(reg, tmp);

	}
}
