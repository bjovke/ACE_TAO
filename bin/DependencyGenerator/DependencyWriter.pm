package DependencyWriter;

# ************************************************************
# Description   : Base class for all Dependency Writers.
# Author        : Chad Elliott
# Create Date   : 2/10/2002
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

# ************************************************************
# Subroutine Section
# ************************************************************

sub new {
  my($class) = shift;
  return bless {
               }, $class;
}


sub process {
  #my($self)    = shift;
  #my($objects) = shift;
  #my($files)   = shift;
  return '';
}


1;
