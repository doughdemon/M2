--- status: Draft
--- author(s): Decker 
--- notes: 

document {
     -- this is the old version, perhaps not completely merged into the new
     Key => radical, 
     Headline => "compute the radical of an ideal",
     TT "radical I", " -- the radical of the ideal I",
     PARA,
     "If I is an ideal in an affine ring (i.e. a quotient of a polynomial 
     ring over a field), and if the characteristic of this field is
     large enough (see below), then this routine yields the radical of
     the ideal I.",
     PARA,
     "The method used is the Eisenbud-Huneke-Vasconcelos algorithm.
     See their paper in Inventiones Mathematicae, 1993, for more details on the
     algorithm.",
     PARA,
     "For an example, see ", TO "component example", ".",
     PARA,
     "The algorithms used generally require that the characteristic of the
     ground field is larger than the degree of each primary component.  In 
     practice, this means that if the characteristic is something like 32003,
     rather than, for example, 5, the methods used will produce the radical of ", TT "I", ".  Of
     course, you may do the computation over ", TO "QQ", ", but it will often run much
     slower.  In general, this routine still needs to be tuned for speed.",
     SeeAlso => {"topComponents", "removeLowestDimension", "saturate", "quotient"}
     }

document { 
     Key => {radical, (radical,Ideal),  (radical,MonomialIdeal)},
     Headline => "Compute the radical of an ideal",
     Usage => "radical I",
     Inputs => {"I" => (Ideal) => ""},
     Outputs => {Ideal => {"the radical of ", TT "I", " ."}},
     "Computes the radical of ", TT "I", " using the Eisenbud-Huneke-Vasconcelos algorithm.
     If ", TT "I", " is  ", OFCLASS MonomialIdeal, ", a faster \"combinatorial\" algorithm is used.",
     EXAMPLE {
	  "R=QQ[x,y]",
	  "I=ideal((x^2+1)^2*y, y+1)",
	  "radical I"
	  },
     Caveat => {"The current implementation requires that the
	  characteristic of the ground field is either zero
	  or a \"large\" prime (unless ", TT "I", " is  ", OFCLASS MonomialIdeal, ")."},
     SeeAlso => {decompose, topComponents, removeLowestDimension, saturate, quotient}
     }


 -- doc10.m2:317:     Key => radical, 
 -- overviewB.m2:368:     Key => "radical of an ideal",



