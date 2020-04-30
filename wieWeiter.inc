<?php
/***
 *** eingefuehrt um Liste evtl. noch nicht verknuepfter 1:N-Instanzen anzuzeigen
 ***/
if( isset($_E["entitaet1N"]) )
{
  $_E["entitaet"] = $_E["entitaet1N"];
  if( isset($_E['countDown']) )
  {
    if( !$_E['countDown'] ) // countDown auf 0
    {
      $_E['wZu'] = "beendendProbandLauf";
      include("forkZu.inc");
    }
    else
      --$_E['countDown'];
  }
}
else if( "einfuegVerknuepfend" == $_E['wZu'] )
{
    $_E['wZu'] = "beendendProbandLauf";
    include("forkZu.inc");
} 
else
{
  echo "\n";?></table><?php
  $_E['wZu'] = "anbietendKnopfZurueck";
  include("forkZu.inc");
}
?>
