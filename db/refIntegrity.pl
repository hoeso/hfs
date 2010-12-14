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

foreach (@a)
{
  if ( /DROP TABLE IF EXISTS `(.*)`/ )
  {
    $w = $1;
    foreach (@t)
    {
  #print "\ndbg: $_\n";
      if( /$w/ )
      { # diese Entitaet ist dran zum Pruefen ...
    print "\ndbg1: $w\n";
        foreach (@a)
        {
          if ( /CREATE TABLE `(.*)`/ )
          {
            $e = $1;
	    $fk = $w . "ID";
    print "\ndbg2: $fk\n";
	    #print "$e pruefen auf $fk\n";
	  }
	  elsif ( $fk && /UNIQUE KEY.*$fk/ )
	  {
	    # IDX ignorieren
	  }
	  elsif ( $fk && /$fk/ )
	  {
            print " ... $fk gefunden in $e\n";
	  }
	}
      }
    }
  }
}
#$paerchen =~ s/jp=.&//;
#$paerchen .= "_sepperl=manuell001";

#print $seite;
