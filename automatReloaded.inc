<?php
if( isset($_E['wZu']) )
  logZustandswechsel($_E['wZu']);
else if( isset($wZu) )
  logZustandswechsel($wZu);
else
  logZustandswechsel('kein Zustand gesetzt?!');
include("wFollowerZu.inc");
?>
