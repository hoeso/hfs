<?php
/************ Input **********************************************************
 * Tabelle    : zu aendernde Tabelle
 * ID	      : ID des Datensatzes mit dem FK
 * FKFeld     : der Name des Foreign Key Feldes
 * SELECTFK   : der neue Foreign Key
 *****************************************************************************/
$sql = "UPDATE $Tabelle SET $FKFeld=$SELECTFK WHERE ID=$ID";
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
  dEcho( $b_, $sql );
}
$result = mysql_db_query( $MySQLDb, $sql );
if(!$result)
{
	reagierenAufSQLFehler( $lkid, $sql, $ID );
}
else
{
	echo "\nDer Eintrag wurde ge&auml;ndert<br>";
}
?>
