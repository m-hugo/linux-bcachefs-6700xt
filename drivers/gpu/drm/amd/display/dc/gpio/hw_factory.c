/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#include "dm_services.h"

/*
 * Pre-requisites: headers required by header of this unit
 */
#include "include/gpio_types.h"

/*
 * Header of this unit
 */

#include "hw_factory.h"

/*
 * Post-requisites: headers required by this unit
 */

#if defined(CONFIG_DRM_AMD_DC_SI)
#include "dce60/hw_factory_dce60.h"
#endif
#include "dce80/hw_factory_dce80.h"
#include "dce110/hw_factory_dce110.h"
#include "dce120/hw_factory_dce120.h"
#include "dcn10/hw_factory_dcn10.h"
#include "dcn20/hw_factory_dcn20.h"
#include "dcn21/hw_factory_dcn21.h"
#include "dcn30/hw_factory_dcn30.h"
#include "dcn315/hw_factory_dcn315.h"
#include "dcn32/hw_factory_dcn32.h"
#include "dcn401/hw_factory_dcn401.h"

bool dal_hw_factory_init(
	struct hw_factory *factory,
	enum dce_version dce_version,
	enum dce_environment dce_environment)
{
	switch (dce_version) {
	case DCN_VERSION_2_0:
		dal_hw_factory_dcn20_init(factory);
		return true;
	case DCN_VERSION_2_01:
	case DCN_VERSION_2_1:
		dal_hw_factory_dcn21_init(factory);
		return true;
	case DCN_VERSION_3_0:
	case DCN_VERSION_3_01:
	case DCN_VERSION_3_02:
	case DCN_VERSION_3_03:
	case DCN_VERSION_3_1:
	case DCN_VERSION_3_14:
	case DCN_VERSION_3_16:
		dal_hw_factory_dcn30_init(factory);
		return true;
	default:
		ASSERT_CRITICAL(false);
		return false;
	}
}
