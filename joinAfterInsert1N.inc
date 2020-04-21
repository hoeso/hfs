<?php
if( !isset($_E) || !isset($_E['FK2join']) || !isset($_E['verbEntitaet']) || !isset($_E['value2Join']) || !isset($_E['entitaet']) || !isset($_eCandy[$_E['entitaet']])  ) // nur wenn vollstaendig uebergeben
  return;

$str = "INSERT INTO $_E[verbEntitaet] ( ID, $_E[FK2join]ID, $_E[entitaet]ID ) VALUES( null, $_E[value2Join], " . $_eCandy[$_E['entitaet']] . " )";

$result = mysql_db_query( $MySQLDb, $str );
?>
