<?php
/*****************************************************************************
 * 12.11.2009 : Das SQL-Statement Array $Select wurde in die Datei sichten.prj
 *              ausgelagert.
 *              Grund: das Generieren eines Ablauf-Diagrammes in wZu.inc
 *                     anhand der Steuer-Variablen fdocC=<Doku-Index>
 *                     erfolgt zusammen mit dem zu zielTabelle gehoerenden
 *                     SQL-Statement. 
 *                     Ein include von anzeigenTabelle.inc in wZu.inc resultiert
 *                     wg. den enthaltenen Funktionsaufrufen in einen Fehler.
 *                     Die Dateien sichten.prj und port.prj koennen dagegen
 *                     bereits in wZu.inc includiert werden.
 *                     
 *****************************************************************************/
include("port.prj");
include("sichten.prj");
function anzeigen( $db, $sql, $table, $ActionSuffix )
{
  global $_eCandy;
  global $fSummeBilden;
  global $Summenwert;
  global $gruppenStaerke;
  $arrNichtAendern=array (
    "ohne submit Knopf",
  /* zum Kopieren
    "",
  */
  );
  if( isset($debug) and $debug )
    echo "$sql<br>";
  $result = mysql_db_query( $db, $sql );
  if(!$result)
  {
    echo "\nFehler beim Ausführen von '$sql'<br>";
    exit;
  }
  spaltenNamenHolen( $result, $spaltenName );
  if( isset($debug) and $debug )
  {
    $n = count($spaltenName);
    echo"\nSpaltenzahl = $n<br>";
  }

  // --- Anzeige formatieren
  $auchIDausgeben = false;
  // ist Zieltabelle Teil der URL?
  $iFarbReihe=0;
  if( isset($_eCandy) )
  {
    foreach( $_eCandy as $k => $elem )
      if( $k == $table and isset($_REQUEST["$k"]) )
      {
        $iFarbReihe=$elem;
        break;
      }
  }
  tabelleBeginnen( $table );
  ausgebenAlsTabellenkopf( $spaltenName, $auchIDausgeben, $cSpalten, $sql, $table, "" );
  //

  $fChecked = false;
  unset($arrFeldTyp);
  for( $z=0; $z<count($spaltenName); $z++ )	// wegen Datumsformatierung
    $arrFeldTyp[$z] = mysql_field_type( $result, $z );
  for( $z=0; $z<count($spaltenName); $z++ )	// wegen enum-Sofortaenderung
    $arrFeldFlag[$z] = mysql_field_flags( $result, $z );
  for( $z=0; $z<count($spaltenName); $z++ )	// wegen enum-Sofortaenderung
    $arrFeldName[$z] = mysql_field_name( $result, $z );

  while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
  {
    tabellenZeileBeginnen();
    $fAendern = true;
    foreach( $arrNichtAendern as $k )
      if( 0 == strcmp( $k, $table ) )
        $fAendern = false;
    if( $fAendern )
      ausgebenAlsTabellenzeileZumAendern( $row, $auchIDausgeben, $fChecked, $arrFeldTyp, $arrFeldFlag, $arrFeldName, $table, $ActionSuffix, $iFarbReihe );
    else
    {
      if( !isset($globalID) )
        $globalID=0;
      ausgebenAlsTabellenzeile( $row, $auchIDausgeben, $fChecked, $spaltenName, $globalID, $arrFeldTyp, $table, $ActionSuffix, "", $dummy );
    }
    tabellenZeileBeenden();
  }

  //
  if( true == $fSummeBilden )
  {
    tabellenZeileBeginnen();
    echo_("\n\t\t<td bgcolor='#E8E8E8' align=right><font size='-2'></font></td>");
    echo_("\n\t\t<td bgcolor='#E8E8E8' align=right><font size='-2'></font></td>");
    tabellenZeileBeenden();
    tabellenZeileBeginnen();
    echo_("\n\t\t<td bgcolor='#E8E8E8' align=right><font size='-2'>Summe:</font></td>");
    $wert = number_format($Summenwert,'2',',','.');
    echo_("\n\t\t<td bgcolor='#E8E8E8' align=right><font size='-2'><b>$wert</b></font></td>");
    tabellenZeileBeenden();
  }
  tabelleBeenden();
  $succ = mysql_free_result( $result );
}
function anzeigenZumAendern( $db, $sql, $table, $globalID, $ActionSuffix = '' )
{
  global $gruppenStaerke;
  if( isset($debug) and $debug )
    echo "$sql<br>";
  $result = mysql_db_query( $db, $sql );
  if(!$result)
  {
    echo "\nFehler beim Ausführen von '$sql'<br>";
    exit;
  }

  echo_("\n<center><H1>$table</H1>");
  hiddenFeldSchreiben( "TabellePK", $table );

  spaltenNamenHolen( $result, $spaltenName );

  // --- Anzeige formatieren
  $auchIDausgeben = true;
  $fChecked = false;// es hat noch keine Vorselektion stattgefunden
  tabelleBeginnen();
  ausgebenAlsTabellenkopf( $spaltenName, $auchIDausgeben, $cSpalten, $sql, $table, "" );
  //

  //$arrFeldTyp = range(0,-1);
  unset($arrFeldTyp);
  for( $z=0; $z<count($spaltenName); $z++ )	// wegen Datumsformatierung
    $arrFeldTyp[$z] = mysql_field_type( $result, $z );
  while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
  {
    tabellenZeileBeginnen();
    ausgebenAlsTabellenzeile( $row, $auchIDausgeben, $fChecked, $spaltenName, $globalID, $arrFeldTyp, $table, $ActionSuffix, "", $dummy );
    tabellenZeileBeenden();
  }

  //
  tabelleBeenden();

  $succ = mysql_free_result( $result );
}
?>
