<?
/************ Input ********************
 * $update     : ist gesetzt, wenn der Satz geaendert werden soll
 * $delete     : ist gesetzt, wenn der Satz geloescht werden soll
 * $delete_x   : ist gesetzt, wenn der Satz geloescht werden soll
 *	         die x-Koordinate vom Bild
 * $ID         : Primaerschluessel des Datensatzes
 * $tableRE    : Name der Tabelle mit dem Primaerschluessel
 ***************************************/
$fDebug=false;


if( isset($delTab) )
{
	echo"\n$delTab<br>";
	exit;
}
if( isset($delete_x) )
    $delete=true;
else if( isset($waehlendBericht) )
{
  $wZu="waehlendBericht";
  include("forkZu.inc");
}
else if( isset($ermittelndGenerierteBerichte) )
{
  $wZu="ermittelndGenerierteBerichte";
  include("forkZu.inc");
}
else if( isset($zeigendDetails) )
{
  $wZu="zeigendDetails";
  include("forkZu.inc");
}
else if( isset($detailsAbrechnung) )
{
  $wZu="zeigendDetailsAbrechnung";
  include("forkZu.inc");
}
else if( isset($detailsArchiv) )
{
  $wZu="zeigendDetailsArchiv";
  include("forkZu.inc");
}
else if( isset($detailsRechnung) )
{
  $wZu="zeigendDetailsRechnung";
  include("forkZu.inc");
}
else if( isset($detailsErledigt) )
{
  $wZu="zeigendDetailsErledigt";
  include("forkZu.inc");
}
else if( isset($zeigendDetailsPortal) )
{
//  $wZu="zeigendDetailsPortal"; mit den Schadennachtraegen beginnen
  $wZu="zeigendNachtragEingang";
  include("forkZu.inc");
}
else if( isset($pruefendVerzug) )
{
  $wZu="pruefendVerzug";
  include("forkZu.inc");
}
else if( isset($zeigendVerzug) )
{
  $wZu="zeigendVerzug";
  include("forkZu.inc");
}
else if( isset($berichtendSub) )
{
  $wZu="berichtendSub";
  include("forkZu.inc");
}
else if( isset($routend) )
{
  $wZu="routendPortal";
  include("forkZu.inc");
}
else if( isset($bestimmendTarif) )
{
  $wZu="bestimmendTarif";
  include("forkZu.inc");
}
else if( isset($abrechnend) )
{
  $wZu="abrechnend";
  include("forkZu.inc");
}
else if( isset($zeigendAnhangGutschrift) )
{
  $wZu="zeigendAnhangGutschrift";
  include("forkZu.inc");
}
else if( isset($zeigendDruckAnsicht) )
{
  $wZu="zeigendDruckAnsicht";
  include("forkZu.inc");
}
else if( isset($zeigendDeckblatt) )
{
  $wZu="zeigendDeckblatt";
  include("forkZu.inc");
}
else if( isset($konvertierendAnhangPauschal) )
{
  $wZu="konvertierendAnhangPauschal";
  include("forkZu.inc");
}
else if( isset($konvertierendDeckblatt) )
{
  $wZu="konvertierendDeckblatt";
  include("forkZu.inc");
}
else if( isset($konvertierendGutschrift) )
{
  $wZu="konvertierendGutschrift";
  include("forkZu.inc");
}
else if( isset($konvertierendRechnung) )
{
  $wZu="konvertierendRechnung";
  include("forkZu.inc");
}
else if( isset($listendSammelrechnung) )
{
  $wZu="listendSammelrechnung";
  include("forkZu.inc");
}
else if( isset($sammelndRechnungen) )
{
  $wZu="sammelndRechnungen";
  include("forkZu.inc");
}
else if( isset($eingebendErstkontakt) )
{
  $wZu="eingebendErstkontakt";
  include("forkZu.inc");
}
else if( isset($eingebendOrtstermin) )
{
  $wZu="eingebendOrtstermin";
  include("forkZu.inc");
}
else if( isset($eingebendAufwand) )
{
  $wZu="eingebendAufwand";
  include("forkZu.inc");
}
else if( isset($angebendPosten) )
{
  $wZu="angebendPosten";
  include("forkZu.inc");
}
else if( isset($zeigendDeckblattGutschrift) )
{
  $wZu="zeigendDeckblattSammelgutschrift";
  include("forkZu.inc");
}
else if( isset($anbietendGutschrift) )
{
  $wZu="hoffend2";
  include("forkZu.inc");
}
else if( isset($hochladendUnterlage) )
{
  $wZu="hochladendUnterlage";
  include("forkZu.inc");
}
else if( isset($hochladendUnterlagePortal) )
{
  $wZu="hochladendUnterlagePortal";
  include("forkZu.inc");
}
else if( isset($hochladendUnterlageArchiv) )
{
  $wZu="hochladendUnterlageArchiv";
  include("forkZu.inc");
}
else if( isset($nachtragend) )
{
  $wZu="nachtragend";
  include("forkZu.inc");
}
else if( isset($nachtragendEingang) )
{
  $wZu="nachtragendEingang";
  include("forkZu.inc");
}
else if( isset($widersprochenHabend) )
{
  $wZu="widersprochenHabend";
  include("forkZu.inc");
}
else if( isset($zeigendDeckblattWartung) )
{
  $wZu="zeigendDeckblattWartung";
  include("forkZu.inc");
}
else if( isset($zeigendAnhangWartung) )
{
  $wZu="zeigendAnhangWartung";
  include("forkZu.inc");
}
else if( isset($zeigendControllingGutschriften) )
{
  $wZu="zeigendControllingGutschriften";
  include("forkZu.inc");
}
else if( isset($diskutierend) )
{
  $wZu="diskutierend";
  include("forkZu.inc");
}
else if( isset($beistellend) )
{
  $wZu="beistellend";
  include("forkZu.inc");
}
else if( isset($antwortend) )
{
  $wZu="antwortend";
  include("forkZu.inc");
}
else if( isset($zeigendDokument) )
{
  $wZu="zeigendDokument";
  include("forkZu.inc");
}
else if( isset($dokumentierend) )
{
  $wZu="dokumentierend";
  include("forkZu.inc");
}

if( isset($richtung) )
{
	$wZu="aenderndPosition";
	include("forkZu.inc");
}

if( isset($delete) )
{
	$delTab=$tableRE;
	$wZu="loeschend";
	include("forkZu.inc");
}
else if( isset($dont) )
{
	echo"\n<p>Der Eintrag wurde nicht gel&ouml;scht.<br>";
	include("knopfZurueck.inc");
	exit;
}

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

/*
	if( false == $hatAttribute )
	{
		echo"<center><h3>'$_E['entitaet']' hat keine &auml;nderbaren Eigenschaften</h3>";
		exit;
	}
*/

	// --- Anzeige formatieren
	$str=$_E['entitaet'];
	$str=str_replace( "ae", "&auml;", $str );
	echo "\n<H3>Eigenschaften von $str &auml;ndern ...</H3>";
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
