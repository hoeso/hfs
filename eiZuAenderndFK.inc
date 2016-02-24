<?php
/** Aufrufendes Skript **** Variable *****************************************
 * anbietenFK.inc	   : Tabelle
 *			   : ID (HIDDEN)
 *			   : SELECTFK
 *			   : FKFeld
 * 
 *****************************************************************************/
if( 0 )
{
  echo"\n<!-- POSTs ... -->";
  foreach( $_POST as $k=>$elem )
    echo"\n<!-- k : $k, elem: $elem -->";
  echo"\n<!-- REQUESTs ... -->";
  foreach( $_REQUEST as $k=>$elem )
    echo"\n<!-- k : $k, elem: $elem -->";
  exit;
}
/* zum Kopieren:
if( isset($_REQUEST[""]) )
  $ = $_REQUEST[""];
*/
if( isset($_REQUEST["Tabelle"]) )
  $Tabelle = $_REQUEST["Tabelle"];
if( isset($_REQUEST["ID"]) )
  $ID = $_REQUEST["ID"];
if( isset($_REQUEST["SELECTFK"]) )
  $SELECTFK = $_REQUEST["SELECTFK"];
if( isset($_REQUEST["FKFeld"]) )
  $FKFeld = $_REQUEST["FKFeld"];
/*** workflow Verzweigung ***/
foreach( $_POST as $k=>$elem )
  if( "aenderndTarif" == $k )
  {
    $wZu=$k;
    include("forkZu.inc");
  }
?>
