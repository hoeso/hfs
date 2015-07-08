<?php
if( isset($Select) && isset($_E['lView']) && isset($Select[ $_E['lView'] ]) )
  $sql = $Select[ $_E['lView'] ];
else if( !isset($Select) )
  $sql = "SELECT NOW(), 'sichten.prj ist nicht includiert.'";
else
  $sql = "SELECT NOW(), 'sichten.prj includiert, doch unbekannter Eintrag'";
?>
