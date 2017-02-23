<?php
$arrNichtAendern=array (
/* zum Kopieren
"",
*/
"Zeitstempel"
);
if( isset($debug) && $debug )
  echo "anzeigen der Tabelle '{$_E['entitaet']}' ...<br>";
if( !isset( $suffix ) )
  $suffix="";
lesenRETabelle( $result, $MySQLDb, $_E['entitaet'], $suffix );
if( !$result && isset($debug) && $debug )
{
  echo "Ist die Tabelle '{$_E['entitaet']}' leer?<br>";
  return;
}
$str=$_E['entitaet'];
$str=str_replace( "ae", "&auml;", $str );
spaltenNamenHolen( $result, $spaltenName );
if( isset($debug) && $debug )
{
  $n = count($spaltenName);
  echo"\nSpaltenzahl = $n<br>";
}

// --- Anzeige formatieren
$auchIDausgeben = false;
// ist Zieltabelle Teil der URL?
$iFarbReihe=0;
foreach( $_eCandy as $k => $elem )
  if( $k == $_E['entitaet'] and isset($_REQUEST["$k"]) )
  {
    $iFarbReihe=$elem;
    break;
  }
tabelleBeginnen();
if( !isset($cSpalten) )
  $cSpalten="";
ausgebenAlsTabellenkopf( $spaltenName, $auchIDausgeben, $cSpalten, "", "", "" );

if( false==isset($keinInsert) )
{
  // Zeile fuer neuen Eintrag...
  tabellenZeileBeginnen();
  formularBeginnen("./mn.php?mn=9422&a={$_E['entitaet']}&b={$_E['entitaet']}%20wird%20gespeichert%20...", "name=frm" . $_E['entitaet'] . " onSubmit='return pruefenEingaben(this)'");
  hiddenFeldSchreiben( "Tabelle", $_E['entitaet'] );
  if( !isset($enumListe[$_E['entitaet']]) and !isset($enumListe[$_E['entitaet'] . "_1"]) )
    ausgebenAlsNeueTabellenzeile( $result, $_E['entitaet'] );
  else
    ausgebenAlsNeueTabellenzeile( $result, $_E['entitaet'], $enumListe[$_E['entitaet']] );
  ?><td><?php
  formularKnopf("neu anlegen", "");
  ?></td></form><?php
  tabellenZeileBeenden();
}

$fChecked = false;
unset($arrFeldTyp);
for( $z=0; $z<count($spaltenName); $z++ )	// wegen Datumsformatierung
  $arrFeldTyp[$z] = mysql_field_type( $result, $z );
for( $z=0; $z<count($spaltenName); $z++ )	// wegen enum-Sofortaenderung
  $arrFeldFlag[$z] = mysql_field_flags( $result, $z );
for( $z=0; $z<count($spaltenName); $z++ )	// wegen enum-Sofortaenderung
  $arrFeldName[$z] = mysql_field_name( $result, $z );
if( !isset($ActionSuffix) )
  $ActionSuffix="";

while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
{
  tabellenZeileBeginnen();
  $fAendern = true;
  foreach( $arrNichtAendern as $k )
    if( 0 == strcmp( $k, $_E['entitaet'] ) )
      $fAendern = false;
    if( $fAendern )
      ausgebenAlsTabellenzeileZumAendern( $row, $auchIDausgeben, $fChecked, $arrFeldTyp, $arrFeldFlag, $arrFeldName, $_E['entitaet'], $ActionSuffix, $iFarbReihe );
    else
    {
      if( !isset($globalID) )
        $globalID=0;
      ausgebenAlsTabellenzeile( $row, $auchIDausgeben, $fChecked, $spaltenName, $globalID, $arrFeldTyp, $_E['entitaet'], $ActionSuffix, "", $dummy );
    }
  tabellenZeileBeenden();
}

tabelleBeenden();
$succ = mysql_free_result( $result );
?>
