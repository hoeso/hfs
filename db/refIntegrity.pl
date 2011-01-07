#!/usr/bin/perl -w

@a = <STDIN>; 

foreach (@a)
{
  if ( /DROP TABLE IF EXISTS `(.*)`/ )
  {
    push(@t,$1); # alle Entitaeten einlesen
  }
}

foreach (@t)
{
  #print "dbg: $_\n";
}

# Vektor eroeffnen ...
print "<?\n\$arrRefs = array(\n";
foreach (@a)
{
  if ( /DROP TABLE IF EXISTS `(.*)`/ )
  {
    $w = $1;
    # diese Entitaet ist dran zum Pruefen ...
    # Logbuch leeren ...
    %log = ();
    print "\n  \"$w\"=>array(\n";
    foreach (@t)
    {
  #print "\ndbg: $_\n";
      if( /$w/ )
      {
        foreach (@a)
        {
          if ( /CREATE TABLE `(.*)`/ )
          {
            $e = $1;
	    $fk = $w . "ID";
	  }
	  elsif ( $fk && /UNIQUE KEY.*$fk/ )
	  {
	    # IDX ignorieren
	  }
	  elsif ( $fk && /$fk/ )
	  {
	    if ( $log{$e} )
	    {
	    }
	    else
	    {
              print "    \"$e\",\n";
	      $log{$e}="1";
	    }
	  }
	}
      }
    }
    # diese Entitaet ist fertig mit geprueft werden.
    if ( %log )
    {
    }
    else
    {
      print "    \"1-leaf\",\n";
    }
    print "  ),\n";
  }
}
# Vektor schliessen ...
print "\n);\n?>";
#$paerchen =~ s/jp=.&//;
#$paerchen .= "_sepperl=manuell001";

#print $seite;
