<?php
if( isset($Select) && isset($_E['lView']) && isset($Select[ $_E['lView'] ]) )
{
  //$_E['sql'] = $Select[ $_E['lView'] ];
  //if( isset($OrderBy) && isset($OrderBy[ $_E['lView'] ]) )
    //$_E['sql'] .= $OrderBy[ $_E['lView'] ];echo $sql . "<br>";
}
else if( !isset($Select) )
  $sql = "SELECT NOW(), 'sichten.prj ist nicht includiert.'";
else
  $sql = "SELECT NOW(), 'sichten.prj includiert, doch unbekannter Eintrag'";
?>
