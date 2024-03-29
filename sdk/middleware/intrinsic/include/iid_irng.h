/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
    This text contains proprietary, confidential information of Intrinsic ID B.V.,
    and may be used, copied, distributed and/or published only pursuant to the
    terms of a valid license agreement with Intrinsic ID B.V.\n
    This copyright notice must be retained as part of this text at all times.
*/

#ifndef _IID_IRNG_H_
#define _IID_IRNG_H_

#include "iid_aes_types.h"

/************************** Public Macros *******************/
#define IRNG_BLOCK_SIZE_BYTES          (16)  /* Size of a Block in bytes.  */

#define IRNG_RANDOM_SEED_SIZE_BYTES    (16)  /* Number of bytes for the seed randomly generated. */

#define IRNG_MINIMUM_SRAM_PUF_BLOCKS   (28)  /* Number of minimum required SRAM PUF blocks. */

/************************** Public Interface ***********************/

/*! \brief Get product information.
 *
 *  \details This function can be used to get the exact name, version and patch
 *         of this software module.
 *
 *  \param[out] *product_id Pointer to a byte buffer that will hold the product identifier.
 *
 *  \param[out] *major_version Pointer to a byte buffer that will hold the major software version.
 *
 *  \param[out] *minor_version Pointer to a byte buffer that will hold the minor software version.
 *
 *  \param[out] *patch Pointer to a byte buffer that will hold the software patch.
 *
 *  \param[out] *build_number Pointer to a byte buffer that will hold the build number.
 *
 *  \returns \ref IID_SUCCESS if success, otherwise another return code.
 */

iid_return_t irng_get_product_info(
                                uint8_t * const product_id,
                                uint8_t * const major_version,
                                uint8_t * const minor_version,
                                uint8_t * const patch,
                                uint8_t * const build_number
                                );

/*! \brief      Get random seed.
 *  \details    This function can be used to get the random seed using
 *              entropy of the sram puf.
 *
 *  \param[in]      *aes_ctx A pointer to a publicly known type struct which holds
 *                  a handle to a device specific user defined aes accelerator environment
 *                  and a device function pointer.
 *
 *  \param[in,out]  *sram_puf A pointer to physical SRAM that will be used
 *                  by IRNG as PUF memory.
 *                  Its address must be aligned to 32 bits
 *
 *  \param[in]      sram_puf_blocks The number of blocks of sram puf to be
 *                  used for entropy.
 *
 *  \param[out]     *random_seed The pointer to the buffer which holds
 *                  the random seed generated by the function.
 *                  Its address must be aligned to 32 bits.
 *
 *  \returns \ref   IID_SUCCESS if success, otherwise another return code.
 */

iid_return_t irng_get_random_seed(
                                        aes_ctx_t*          aes_ctx,
                                        uint8_t  *          sram_puf,
                                const   uint16_t            sram_puf_blocks,
                                        uint8_t  *  const   random_seed
                                );

#endif /* _IID_IRNG_H_ */
