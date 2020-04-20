<?php
if( !isset($_E) || !isset($_E) || !isset($_E['FK2join']) || !isset($_E['verbEntitaet']) || !isset($_E['value2Join']) || !isset($_E['entitaet']) || !isset($_eCandy[$_E['entitaet']])  ) // nur wenn vollstaendig uebergeben
  return;

$str = "INSERT INTO $_E['verbEntitaet'] VALUES( null, $_REQUEST[ID2join], $_E[ID] )";
$result = mysql_db_query( $MySQLDb, $str );
if( isset($_E) and isset($_E['entitaet']) and isset($_eCandy) and isset($_eCandy[$_E['entitaet']]) )
{
  $_E['entitaet'] = $_REQUEST['entitaet2join'] . $_E['entitaet'];
  $sql = "SELECT LAST_INSERT_ID() FROM " . $_E['entitaet'];
  $result = mysql_db_query( $MySQLDb, $sql );
  $arr = mysql_fetch_row( $result );
  $_eCandy[$_E['entitaet']] = $arr[0]; // damit wird auf die gerade angelegte Instanz in ihrer Liste positioniert
  mysql_free_result( $result );
}
?>
