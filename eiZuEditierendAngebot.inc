<?php
/** 1. aufrufendes Skript **** Variable *****************************************
 * editierendAngebot   : ID (EDV.ID)
 *                     : 
 *****************************************************************************/
if( 0 )
{
  echo "POST:<br>";
  foreach( $_POST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  echo "REQUEST:<br>";
  foreach( $_REQUEST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
}
/* zum Kopieren:
if( isset($_REQUEST[""]) )
  $ = $_REQUEST[""];
*/
$_E['entitaet']="Angebot";
$_E['recipient']=9422; // speicherndRE
$countSL=1;
$tableSL1="EDV";
$SL1="SELECT ID, Projekt FROM EDV WHERE ID={$_REQUEST['ID']}";
$gruppenStaerke=3;
$Select['Angebot'] .= " AND Angebot.EDVID={$_REQUEST['ID']}";
if( 'ja' == gibFeld( $MySQLDb, "SELECT PDF FROM EDV WHERE ID={$_REQUEST['ID']}", 0 ) )
  $fKeinUpdate = $fKeinDelete = true;
?>
