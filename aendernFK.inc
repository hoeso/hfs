<?php
/************ Input **********************************************************
 * Tabelle    : zu aendernde Tabelle
 * ID	      : ID des Datensatzes mit dem FK
 * FKFeld     : der Name des Foreign Key Feldes
 * SELECTFK   : der neue Foreign Key
 *****************************************************************************/
$sql = "UPDATE $_E[entitaet] SET $_E[FKFeld]=$_E[SELECTFK] WHERE ID=$_E[ID]";
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
