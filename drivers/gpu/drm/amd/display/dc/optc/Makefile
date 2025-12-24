
# Copyright 2022 Advanced Micro Devices, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# Makefile for the 'optc' sub-component of DAL.
#


ifdef CONFIG_DRM_AMD_DC_FP
###############################################################################
# DCN
###############################################################################

OPTC_DCN10 = dcn10_optc.o

AMD_DAL_OPTC_DCN10 = $(addprefix $(AMDDALPATH)/dc/optc/dcn10/,$(OPTC_DCN10))

AMD_DISPLAY_FILES += $(AMD_DAL_OPTC_DCN10)

###############################################################################

OPTC_DCN20 = dcn20_optc.o

AMD_DAL_OPTC_DCN20 = $(addprefix $(AMDDALPATH)/dc/optc/dcn20/,$(OPTC_DCN20))

AMD_DISPLAY_FILES += $(AMD_DAL_OPTC_DCN20)

###############################################################################

OPTC_DCN201 = dcn201_optc.o

AMD_DAL_OPTC_DCN201 = $(addprefix $(AMDDALPATH)/dc/optc/dcn201/,$(OPTC_DCN201))

AMD_DISPLAY_FILES += $(AMD_DAL_OPTC_DCN201)

###############################################################################

###############################################################################

###############################################################################

OPTC_DCN30 = dcn30_optc.o

AMD_DAL_OPTC_DCN30 = $(addprefix $(AMDDALPATH)/dc/optc/dcn30/,$(OPTC_DCN30))

AMD_DISPLAY_FILES += $(AMD_DAL_OPTC_DCN30)

###############################################################################

OPTC_DCN301 = dcn301_optc.o

AMD_DAL_OPTC_DCN301 = $(addprefix $(AMDDALPATH)/dc/optc/dcn301/,$(OPTC_DCN301))

AMD_DISPLAY_FILES += $(AMD_DAL_OPTC_DCN301)

endif

