<?
/************ Input ********************
 * $update     : ist gesetzt, wenn der Satz geaendert werden soll
 * $_E['loeschen']     : ist gesetzt, wenn der Satz geloescht werden soll
 * $delete_x   : ist gesetzt, wenn der Satz geloescht werden soll
 *	         die x-Koordinate vom Bild
 * $ID']         : Primaerschluessel des Datensatzes
 * $tableRE    : Name der Tabelle mit dem Primaerschluessel
 ***************************************/
$fDebug=false;


if( isset($delTab) )
{
	echo"\n$delTab<br>";
	exit;
}
if( isset($richtung) )
{
	$wZu="aenderndPosition";
	include("forkZu.inc");
}

/*** Block wird in mn.prj erledigt: if( isset($dont) )
{
	echo"\n<p>Der Eintrag wurde nicht gel&ouml;scht.<br>";
        $_E['wZu']="anbietendKnopfZurueck";
        include("forkZu.inc");
}***/

if( isset($zoom) )
{
	$Titel=$zoom;
	$wZu="anzeigendKinder";
	include("forkZu.inc");
}
if( isset($rauf_x) )
	$richtung="kleiner";
else if( isset($runter_x) )
	$richtung="groesser";
if( isset($richtung) )
{
	$wZu="aenderndPosition";
	include("forkZu.inc");
}
if( isset($debug) && $debug )
	echo "\nanzeigen der Tabelle '{$_E['entitaet']}' mit ID={$_E['ID']} ...<br>";
include("editierenRE.prj");

lesenRETabelle( $result, $MySQLDb, $_E['entitaet'], " WHERE ID={$_E['ID']}" );
if( $result )
{
	spaltenNamenHolen( $result, $spaltenName );
	$n = count($spaltenName);
	if( isset($debug) && $debug )
	{
	    echo"\nSpaltenzahl = $n<br>";
	}
	$hatAttribute = false;
	for( $i=0; $i<$n; $i++)
	     if( false == istForeignKeyName( $spaltenName[$i] ) )
		 $hatAttribute = true;

	// --- Anzeige formatieren
	$str=$_E['entitaet'];
	$str=str_replace( "ae", "&auml;", $str );
	//echo "\n<H3>Eigenschaften von $str &auml;ndern ...</H3>";
	$auchIDausgeben = false;
	tabelleBeginnen();
	if( isset($backupSELECTSL1) )
	    $ActionSuffix = "&TabelleSL1=$TabelleSL1&backupSELECTSL1=$backupSELECTSL1";
	else
	  $ActionSuffix = "";
	if( isset($goto) )
	     $ActionSuffix .= "&goto=true";
   if( !isset($cSpalten) )
     $cSpalten="";
if( isset( $globalCandy ) )
  foreach( $globalCandy as $k => $elem )
    if( $elem )
    {
      $ActionSuffix .= $candyURL[$k];
      $ActionSuffix .= "&$k=$elem";
    }
	ausgebenAlsTabelleZumVertikalenAendern( $spaltenName, $auchIDausgeben, $cSpalten, "", "", $result, $_E['entitaet'], $_E['ID'], $ActionSuffix );
	//
	tabelleBeenden();
	$succ = mysql_free_result( $result );
}
else if( $debug )
	echo "Ist die Tabelle '{$_E['entitaet']}' leer?<br>";
?>
