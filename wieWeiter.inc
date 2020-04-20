<?php
/***
 *** eingefuehrt um Liste evtl. noch nicht verknuepfter 1:N-Instanzen anzuzeigen
 ***/
if( isset($_E["entitaet1N"]) )
{
  $_E["entitaet"] = $_E["entitaet1N"];
}
else
{
  echo "\n";?></table><?php
  $_E['wZu'] = "anbietendKnopfZurueck";
  include("forkZu.inc");
}
?>
