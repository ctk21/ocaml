/**************************************************************************/
/*                                                                        */
/*                                 OCaml                                  */
/*                                                                        */
/*      KC Sivaramakrishnan, Indian Institute of Technology, Madras       */
/*                Stephen Dolan, University of Cambridge                  */
/*                                                                        */
/*   Copyright 2019 Indian Institute of Technology, Madras                */
/*   Copyright 2019 University of Cambridge                               */
/*                                                                        */
/*   All rights reserved.  This file is distributed under the terms of    */
/*   the GNU Lesser General Public License version 2.1, with the          */
/*   special exception on linking described in the file LICENSE.          */
/*                                                                        */
/**************************************************************************/

#ifndef CAML_STATE_H
#define CAML_STATE_H

#include <stddef.h>
#include "misc.h"
#include "mlvalues.h"

#undef young_ptr
#undef young_limit
#undef young_start
#undef young_end
#undef local_roots

/* This structure sits in the TLS area and is also accessed efficiently
 * via native code, which is why the indices are important */
typedef struct {
#define DOMAIN_STATE(type, name) CAMLalign(8) type name;
#include "domain_state.tbl"
#undef DOMAIN_STATE
} caml_domain_state;

enum {
  Domain_state_num_fields =
#define DOMAIN_STATE(type, name) + 1
#include "domain_state.tbl"
#undef DOMAIN_STATE
};

/* Check that the structure was laid out without padding,
   since the runtime assumes this in computing offsets */
CAML_STATIC_ASSERT(
  sizeof(caml_domain_state) ==
   (Domain_state_num_fields
   ) * 8);

CAMLextern caml_domain_state* Caml_state;

#include "compatibility.h"

#endif /* CAML_STATE_H */
