// Copyright 2005 Michael E. Stillman.

#include "res-gausser.hpp"
#include "res-f4-mem.hpp"
#include "moninfo.hpp"

ResGausser *ResGausser::newResGausser(const Ring *K)
{
  const Z_mod *Kp = K->cast_to_Z_mod();
  if (Kp != 0)
    return new ResGausser(Kp);
  return 0;
}

ResGausser::ResGausser(const Z_mod *K0)
  : typ(ZZp), K(K0), Kp(K0->get_CoeffRing()), n_dense_row_cancel(0), n_subtract_multiple(0)
{
}

ResGausser::CoefficientArray ResGausser::from_ringelem_array(ComponentIndex len, ring_elem *elems) const
{
  int i;
  switch (typ) {
  case ZZp:
    int *result = Mem.coefficients.allocate(len);
    for (i=0; i<len; i++)
      result[i] = elems[i].int_val;
    return result;
  };
  return 0;
}

void ResGausser::to_ringelem_array(ComponentIndex len, CoefficientArray F, ring_elem *result) const
{
  int* elems = F;
  int i;
  switch (typ) {
  case ZZp:
    for (i=0; i<len; i++)
      result[i].int_val = elems[i];
  };
}

void ResGausser::deallocate_F4CCoefficientArray(CoefficientArray &F, ComponentIndex len) const
{
  int* elems = F;
  switch (typ) {
  case ZZp:
    Mem.coefficients.deallocate(elems);
    F = 0;
  };
}
/////////////////////////////////////////////////////////////////////
///////// Dense row routines ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void ResGausser::dense_row_allocate(dense_row &r, ComponentIndex nelems) const
{
  int *elems = Mem.coefficients.allocate(nelems);
  r.coeffs = elems;
  r.len = nelems;
  for (ComponentIndex i=0; i<nelems; i++)
    Kp->set_zero(elems[i]);
}

void ResGausser::dense_row_clear(dense_row &r, ComponentIndex first, ComponentIndex last) const
{
  int* elems = r.coeffs;
  for (ComponentIndex i=first; i<=last; i++)
    Kp->set_zero(elems[i]);
}

void ResGausser::dense_row_deallocate(dense_row &r) const
{
  deallocate_F4CCoefficientArray(r.coeffs, r.len);
  r.len = 0;
}

void ResGausser::dense_row_fill_from_sparse(dense_row &r,
                                         ComponentIndex len,
                                         CoefficientArray sparse,
                                         ComponentIndex *comps) const
{
  int* elems = r.coeffs;
  int* sparseelems = sparse;
  for (ComponentIndex i=0; i<len; i++)
    elems[*comps++] = *sparseelems++;

}

ComponentIndex ResGausser::dense_row_next_nonzero(dense_row &r, ComponentIndex first, ComponentIndex last) const
{
  int* elems = r.coeffs;
  elems += first;
  for (ComponentIndex i=first; i<=last; i++)
    if (!Kp->is_zero(*elems++))
      return i;
  return last+1;
}

void ResGausser::dense_row_cancel_sparse(dense_row &r,
                                      ComponentIndex len,
                                      CoefficientArray sparse,
                                      ComponentIndex *comps) const
{
  int* elems = r.coeffs;
  int* sparseelems = sparse;

  // Basically, over ZZ/p, we are doing: r += a*sparse,
  // where sparse is monic, and a is -r.coeffs[*comps].

  n_dense_row_cancel++;
  n_subtract_multiple += len;
  int a = elems[*comps];
  for (ComponentIndex i=len; i>0; i--)
    Kp->subtract_multiple(elems[*comps++], a, *sparseelems++);
}

// Local Variables:
// compile-command: "make -C $M2BUILDDIR/Macaulay2/e "
// indent-tabs-mode: nil
// End:
