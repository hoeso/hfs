<?php
if( isset($backupSELECTSL1) and $backupSELECTSL1 )
  $ActionSuffix = "&TabelleSL1=$TabelleSL1&backupSELECTSL1=$backupSELECTSL1";

if( isset($NurPKEinfuegen) and $NurPKEinfuegen )
{   // dann kam der Aufruf wohl nicht aus zuordnen.php, sondern aus aufbauenListen.php
  $sql = $SelectNurPK[$zielTabelle];
}
else if( isset($zielTabelle) )
  $sql = $Select[$zielTabelle];

if( isset($zielTabelle) and isset($autoID) )
  $sql .= " and " . $zielTabelle . ".ID=" . $autoID;

//echo "\n<!-- $sql -->";
?>
