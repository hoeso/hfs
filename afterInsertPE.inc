<?php
if( isset($_E) and isset($_E['entitaet']) and isset($_eCandy) and isset($_eCandy[$_E['entitaet']]) )
{
  $sql = "SELECT LAST_INSERT_ID() FROM " . $_E['entitaet'];
  $result = mysql_db_query( $MySQLDb, $sql );
  $arr = mysql_fetch_row( $result );
  $_eCandy[$_E['entitaet']] = $arr[0]; // damit wird auf die gerade angelegte Instanz in ihrer Liste positioniert
  mysql_free_result( $result );
}
?>
