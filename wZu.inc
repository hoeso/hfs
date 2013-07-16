<?php
include("automat.inc");

function logModul( $str )
{
  echo"\n<!-- Modul $str: -->\n";
}
foreach( $automat[$_E['wZu']] as $include )
{
  logModul($include);
  include($include);
}
?>
</BODY>
</HTML>
