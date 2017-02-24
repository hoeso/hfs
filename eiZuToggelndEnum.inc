<?php
/** Aufrufendes Skript **** Variable *****************************************
 * anzeigeRoutinen.php       : wert
 *                           : table
 *                           : feld
 *                           : ID
 *                           : 
 *****************************************************************************/
if( 0 )
{
  echo"\n<!-- POSTs ... -->";
  foreach( $_POST as $k=>$elem )
    echo"\n<!-- k : $k, elem: $elem -->";
  echo"\n<!-- REQUESTs ... -->";
  foreach( $_REQUEST as $k=>$elem )
    echo"\n<!-- k : $k, elem: $elem -->";
  //exit;
}
/* zum Kopieren:
if( isset($_REQUEST[""]) )
  $ = $_REQUEST[""];
*/
if( isset($_REQUEST["ID"]) )
  $ID = $_REQUEST["ID"];
if( isset($_REQUEST["feld"]) )
  $feld = $_REQUEST["feld"];
if( isset($_REQUEST["table"]) )
{
  $table = $_REQUEST["table"];
  if( "RueckspracheSub" == $table )
    $table = "Ruecksprache";
}
if( isset($_REQUEST["wert"]) )
  $wert = $_REQUEST["wert"];
?>
