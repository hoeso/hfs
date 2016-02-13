<?php
function einfuegenAusschlussKriterium( $db, $lkid, $tabelle, &$sql )
{
$ausschliesser = array(
	"Niederlassung"=>array(
		"aktiv",
		"nein"
	),
);
  $result = mysql_list_tables( $db, $lkid );
  if(!$result)
    reagierenAufSQLFehler( $lkid, $dummy, $dummy );
  $nTabellen = mysql_num_rows( $result );
  for( $i=0; $i < $nTabellen; $i++ )
  {
    $name = mysql_tablename( $result, $i );
    if( isset($ausschliesser["$tabelle"]) and $tabelle == $name )
    {// Listenauswahl aus Tabelle mit Ausschlusskriterium?
      $c = 0;
      foreach( $ausschliesser["$name"] as $wert )
      {// Feld und Kriterium uebernehmen in Variablen
        !$c ? $feld = $wert : $krit = $wert;
        ++$c;
      }
      $sql = $sql . " AND $name.$feld <> '" . $wert . "'";
    }
  }
}

function zeilenSortieren( $zc, $nSpalten, &$zeilen, &$Mid )
{
	if( !$zc )
	    return;
	$a=0;
	for( $i=0; $i < $zc; )
	{
		if( isset($aZeile[$a]) )
		{
		  unset($aZeile[$a]);
      $aZeile[$a]='';
		}
	  for( $j=0; $j < $nSpalten; $j++, $i++ )
	  {
			if( !isset($aZeile[$a]) )
			  $aZeile[$a]="";
		  $aZeile[$a] .= $zeilen[$i];  
		  $aZeile[$a] .="|";// als Delimiter verwenden
		}
		$aZeile[$a] = trim($aZeile[$a]);// Leerzeichen vorne und hinten entfernen
		$aZeile[$a] .="$Mid[$a]";
		$a++;

	}
	sort($aZeile);
	$i=0;
	$a=0;
	foreach( $aZeile as $az )
	{
		$arr = explode( "|", $az );// 
		foreach( $arr as $azz )
		{
			$zeilen[$i] = $azz;
			if( 1 < $nSpalten )// Gruppierung zeigen
			    $zeilen[$i] .= ">";
			$i++;
		}
		$i--;
		$Mid[$a]=$zeilen[$i];
		$Mid[$a] = str_replace(">","",$Mid[$a]);// letztes > Zeichen entfernen
		$a++;
		unset($zeilen[$i]);// diese Variable enthielt noch die ID
		$zeilen[$i-1] = str_replace(">","",$zeilen[$i-1]);// letztes > Zeichen entfernen
	}
}

function spaltenNamenHolen( $result, &$spaltenName )
{
	$n = mysql_num_fields($result);
	for( $i=0; $i < $n; $i++ )
	     $spaltenName[$i] = mysql_field_name( $result, $i );
}
// Inhalt ausgeben einer Tabelle
function lesenRETabelle( &$result, $db, $table, $suffix )
{
  global $BOGesID;
  global $lkid;
  include "dbRoutinen.prj";
  $sql = "SELECT * FROM $table ";
  if( $suffix )
    $sql .= $suffix;
  else if( isset($hashMandant[$table]) )
  {
    $mandant = $hashMandant[$table];
    $result = mysql_db_query( $db, $sql );
    if(!$result)
      reagierenAufSQLFehler( $lkid, $sql, $ID );
    $nFelder = mysql_num_fields( $result );
    $sql = "SELECT ID";
    for( $i=1; $i < $nFelder; $i++ )
    {
      $feldname = mysql_field_name( $result, $i );
      if( $mandant == $feldname )
        continue;// das Filterfeld auslassen
      $sql .= ", $feldname";
    }
    mysql_free_result( $result );
    $sql .= " FROM $table WHERE $mandant = $hashKey[$mandant]";
  }
  if( $suffix and isset($appendix[$table]) )
    $sql .= " $appendix[$table]";
  else if( isset($appendix[$table]) )
    $sql .= " $appendix[$table]";

  $result = mysql_db_query( $db, $sql );
  if(!$result)
    reagierenAufSQLFehler( $lkid, $sql, $ID );

  if( "Zeitstempel" == $table )
    return true;
  return false;
}
// gibFeld
// Input:
//	$sql: Select
//	$iFeld: das iFeld.te Feld soll zurückgegeben werden
//
function gibFeld( $db, $sql, $iFeld )
{
	$result = mysql_db_query( $db, $sql );
	//	echo"\n<!-- $sql -->";
	if(!$result)
	{
		reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	}
	$arr = mysql_fetch_row( $result );
	$anz=count($arr);
	mysql_free_result( $result );
	return $arr[ $iFeld ];	
}
function gibFeldArray( $db, $sql, $iFeld, &$arrFeld )
{
	$result = mysql_db_query( $db, $sql );
	//	echo"\n<!-- $sql -->";
	if(!$result)
	{
		reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	}
	$nTreffer = mysql_num_rows( $result );
	for( $i=0; $i<$nTreffer;$i++ )      // ueber alle Datensaetze
	{
		$arr = mysql_fetch_row( $result );
		$arrFeld[$i] = $arr[$iFeld];
	}
	mysql_free_result( $result );
}
function gibFelderArray( $db, $sql, &$arrFeld )
{
	$arrTmp=$arrFeld;
	$anz=count($arrTmp);
	$result = mysql_db_query( $db, $sql );
	//	echo"\n<!-- $sql -->";
	if(!$result)
	{
		reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	}
	$nTreffer = mysql_num_rows( $result );
	$j=0;

	for( $i=0; $i<$nTreffer;$i++ )      // ueber alle Datensaetze
	{
		$arr = mysql_fetch_row( $result );
		for($k=0;$k<$anz;$k++)
		{
			$arrFeld[ $j++ ] = $arr[ $arrTmp[ $k ] ];
		}
	}
	mysql_free_result( $result );
}
/********************************************************
 * liefert nur die Attributwerte des ersten Treffersatzes
 ********************************************************/
function gibFelder( $db, $sql, &$arrFeld )
{
	$result = mysql_db_query( $db, $sql );

	if(!$result)
	{
		reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	}
	$arr = mysql_fetch_row( $result );
	$anz=count($arrFeld);
	mysql_free_result( $result );
	for($i=0;$i<$anz;$i++)
	{
		$arrFeld[ $i ] = $arr[ $arrFeld[ $i ] ];
	}
}
function gibFeldname( $db, $sql, $iFeld )
{
	$result = mysql_db_query( $db, $sql );
	echo"\n<!-- $sql -->";
	if(!$result)
	{
		reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	}
	$name = mysql_field_name( $result, $iFeld );
	mysql_free_result( $result );
	return $name;	
}
// Inhalt ausgeben einer Tabelle
function lesenTabelleMitID( $db, $sql, &$nSpalten, &$Mid, &$zeilen )
{
	$result = mysql_db_query( $db, $sql );
	if(!$result)
	{
		echo "Fehler beim Ausführen von '$sql'<br>";
		return;
	}

       // Der Primaerschluessel ist immer das 1. Feld
       $PK = 0;
       $Midc = 0;
//	$zeilen = range(0,-1);
//	$Mid = range(0,-1);

	$nTreffer = mysql_num_rows( $result );
	$nFelder = mysql_num_fields( $result );
	$nSpalten = $nFelder-1;
	$zc = 0;

	for( $i=0; $i<$nTreffer;$i++ )      // ueber alle Datensaetze
	{
		$arr = mysql_fetch_row( $result );
		$Mid[$Midc++] = $arr[$PK];
		for( $f=1; $f<$nFelder; $f++ ) //ueber alle Felder
		{
			$zeilen[$zc] = $arr[$f];
			$zc++;
		}
	}
	if( isset($debug) and $debug )
	    echo"\nSpalten : $nSpalten; Treffer : $nTreffer; zeilen : $zc<br>";

	zeilenSortieren( $zc, $nSpalten, $zeilen, $Mid );

	$succ = mysql_free_result( $result );
}

function suchenMitPK( $db, $table, $arr, &$nTreffer, &$ID, &$arr2 )
{
	$sql = "SELECT ID FROM $table WHERE ";
	$fGo = true;
	foreach( $arr as $k=>$elem )
	{
		if( $fGo )
		{
			$fGo = false;
			$sql .= "$k = $elem";
		}
		else
			$sql .= " AND $k = $elem";
	}

	$result = mysql_db_query( $db, $sql );
	if(!$result)
	{
		echo "\n$sql<br>";
		return false;
	}
	$nTreffer = mysql_num_rows( $result );
	if( $nTreffer > 0 )
	{
		$arr2 = mysql_fetch_row( $result );
		$ID = $arr2[0];
	}	
	mysql_free_result( $result );
	return true;
}
/******************************************************************************
 * $arrPK	: Array mit den FK-Feldnamen
 *****************************************************************************/
function speichernPKsUndAttr( $lkid, $db, $table, $arrPK, $arrAttr,$UniquePK, &$sql, &$ID )
{
  $ID = 0;
  $sql = "INSERT INTO $table (ID";

  foreach( $arrPK as $k=>$elem )
    $sql .= ", $k";

  /****************************************
   * Die Attribute in $k kommen in der Form
   * {zielTabelle}_{Feldtyp}_{Feldname}
   ****************************************/
  if( count($arrAttr) )
  {
    foreach( $arrAttr as $k=>$elem )
    {
      $arr = explode( "_", $k );
      $sql .= ", $arr[2]";
    }
  }	
  $sql .= ") VALUES (null";

  foreach( $arrPK as $k=>$elem )
  {
    $sql .= ", $elem";
  }

  if( count($arrAttr) )
  {
    foreach( $arrAttr as $k=>$elem )
    {
      $arr = explode( "_", $k );
      switch( $arr[1] )
      {
	case "date":
          if( $elem )
          {
            $aDate = explode(".",$elem);
            $sql .= ", '".$aDate[2]."-".$aDate[1]."-".$aDate[0]."'";
          }
          else
            $sql .= ", ''";
        break;
	case "int":
				     $sql .= ", $elem";
				     break;
				case "real":
				     unset( $aDP );
				     $aDP = explode( ",", $elem );
				     if( 1 < count($aDP) )
					 $elem = "$aDP[0].$aDP[1]";
				     $sql .= ", $elem";
				     break;
				case "string":
				     $sql .= ", '".$elem."'";
				     break;
				case "time":
				     $sql .= ", '".$elem."'";
				     break;
				case "blob":
				     $sql .= ", '".$elem."'";
				     break;
				default:
					echo "unbekannter Datentyp $arr[1]<br>";
			}
		}
	}	

	$sql .= ")";

	if( isset($debug) )
		echo "\n$sql<br>";
	include("beforeInsertERM.prj");
	$result = mysql_db_query( $db, $sql );
	if($result)
		return true;

	reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	if( !$UniquePK )
	    return false;
	if( false == $PKViolation )
	    return false;

	$sql = "SELECT ID FROM $table WHERE ";
	$first = true;
	foreach( $arrPK as $k=>$elem )
	{
		if( $first )
			$first = false;
		else
			$sql .= " AND ";
		$sql .= "$k=$elem";
	}
	echo"\n<!-- $sql -->";
	$result = mysql_db_query( $db, $sql );
	if(!$result)
		return false;
	$arr = mysql_fetch_row( $result );
	$ID=$arr[0];
	mysql_free_result( $result );
	return false;
}

function gibEinmaligenRecord( $db, $arr, &$sql, &$nTreffer )
{
	$sql = "SELECT * FROM ";
	foreach( $arr as $k=>$elem )
	{
		$str = strstr( $k, "Tabelle" );
		if( $str ) {
		    $sql .= $elem . " WHERE ";
		    continue;
		}
		$str = strstr( $k, "Feld1" );
		if( $str ) {
		    $sql .= $elem . " = ";
		    continue;
		}
		$str = strstr( $k, "Feld" );
		if( $str ) {
		    $sql .= " AND $elem = ";
		    continue;
		}
		$str = strstr( $k, "Wert" );
		if( $str ) {
		    $sql .= $elem;
		    continue;
		}
	}

	$result = mysql_db_query( $db, $sql );
	if(!$result)
	{
		return false;
	}
	$nTreffer = mysql_num_rows( $result );
	mysql_free_result( $result );

	return true;
}
/**********************************
 * uebergeben wird ein Select-Statement auf eine junction entity
 * , also auf eine Verbindungsentität zweier Tabellen
 * so wird eine M:M-Beziehung aufgelöst
 * ------------------------------------------
 * Der erhaltene Datensatz wird analysiert:
 * Die ID der je wird ignoriert
 * Aus den folgenden Feldern wird vom Feldnamen
 * der Name der verknüpften Tabellen ausgelesen nach $tabKopf[]
 * (Das geht so, weil der verknuepfte Feldname besteht aus dem Namen
 * der Tabelle, deren Primaerschluessel das Feldattribut ist, und
 * der Endung "ID")
 * und ein Select-Statement auf diese Tabelle gebastelt mit dem
 * verknüpften Primaerschluessel.
 * Die Statements werden in das Array $arr[] gestellt
 * -------------------------------------------
 * in einer 2. Schleife werden die Statements ausgeführt und
 * der Wert des 2. Feldes des erhaltenen Datensatzes in das
 * Array $zeilen[] gestellt
 * Schliesslich wird die Tabellenfunktion zur Anzeige aufgerufen
 ******************************************************************/
function auslesenZuordnung( $db, $sql, &$tabKopf, &$JEid, &$zeilen )
{
	$result = mysql_db_query( $db, $sql );	// muss ein eindeutiger Treffer sein
	if(!$result)
	{
		return false;
	}
	// 1. Schritt: Tabellenkopf ermitteln + 1. Verknüpfung auslesen
	$row=mysql_fetch_array( $result, MYSQL_ASSOC );
	$id = true;   // Option Value ist die ID
	$i = 0;
	$j = 0;
	$m = 0;
	foreach( $row as $k=>$elem )
	{
		if( $id )
		{
			$JEid[$m++] = $elem;
			$id = false;
			continue;
		}
		// Namen der verknuepften Tabelle ermitteln
		if( false == istForeignKeyName( $k ) )
		  continue;// Attribut ignorieren
		$tabKopf[ $j++ ] = str_replace( "ID", "", $k );
		$arr[ $i ] = "SELECT * FROM " . $tabKopf[ $j-1 ];
		$arr[ $i++ ] .= " WHERE ID = " . $elem;
	}
	// 2. Schritt: die restlichen Verknuepfungen auslesen
	while( $row=mysql_fetch_array( $result, MYSQL_ASSOC ) )
	{
		$id = true;   // Option Value ist die ID
		foreach( $row as $k=>$elem )
		{
			if( $id )
			{
				$JEid[$m++] = $elem;
				$id = false;
				continue;
			}
			else if( false == istForeignKeyName( $k ) )
		  	  continue;// Attribut ignorieren
			$arr[ $i ] = "SELECT * FROM " . str_replace( "ID", "", $k );
			$arr[ $i++ ] .= " WHERE ID = " . $elem;
		}
	}

	if( isset($debug) and $debug )
		for( $j = 0; $j < $i; $j++ )
		     echo "\n$arr[$j] <br>";
	mysql_free_result( $result );
	$anz = count( $arr );
	for( $i=0; $i < $anz; $i++ )
	{
		$result = mysql_db_query( $db, $arr[$i] );	// muss ein eindeutiger Treffer sein
		if(!$result)
		{
			return false;
		}
		$attr = mysql_fetch_row( $result );
		$zeilen[$i] = $attr[1];		     
	}
	if( $i )
	{
		zeilenSortieren( $i, count($tabKopf), $zeilen, $JEid );
		mysql_free_result( $result );
	}
}
function auslesenEMKette( $db, $table, &$tabKopf, &$Mid, &$zeilen, &$t, &$textname )
{
//$fDebug=1;
  // Der erste Foreign Key einer verknuepften Entitaet steht hinter
  // ihrem Primaerschluessel 
  $FKeins = 1;
  $textFeldNr = 2;
  $textc = 0;
  $t[ 0 ] = $table; // Array ueber die Anzahl der  1:M-verketteten Tabellennamen
  $tc = 1;	 // Zaehler ueber die Anzahl der  1:M-verketteten Tabellen

  // 1. Durchlauf: Anzahl der verketteten Tabellen feststellen

  $result = mysql_db_query( $db, "SELECT * FROM $table" );
  if(!$result)
  {
    return false;
  }
  $textname[$textc++] = mysql_field_name( $result, $textFeldNr);
  $feldname = mysql_field_name( $result, $FKeins );// indiziert ab Element 0

  $len = strlen($feldname) - 2;
  $str = substr($feldname, $len, 2); 

  while( strstr($str, "ID" ) )
  {
    if( isset($fDebug) )
      echo"feldname: $feldname<br>";
    $t[ $tc ] = str_replace( "ID", "", $feldname );// Die verketteten Tabellennamen merken
    $arr = mysql_fetch_row( $result );

    mysql_free_result( $result );
    $sql = "SELECT * FROM " . $t[$tc] . " WHERE " . $t[$tc] . ".ID=" . $arr[$FKeins];
    $result = mysql_db_query( $db, $sql );
    if(!$result)
    {
      return false;
    }
    if( isset($fDebug) )
      echo"$sql<br>";

    $feldname = mysql_field_name( $result, $FKeins );// indiziert ab Element 0

    $len = strlen($feldname) - 2;
    $str = substr($feldname, $len, 2); 
    $dummy = $t[$tc]; // das naechste Kommando ueberschreibt $t[$tc] !!!!!!!!
    if( strstr($str, "ID" ) )
      $textname[$textc++] = mysql_field_name( $result, $textFeldNr );
    $t[$tc] = $dummy;
    if( isset($fDebug) )
      echo "\nt[$tc] = $t[$tc]<br>";
    $tc++;
  }
  // Am Ende der Kette steht die Bezeichnung schon im 2. Feld,
  // weil die Tabelle eine reine Entitaet ist.
  // Das ist zugleich das Ende-Kriterium dieses Durchlaufs	
  $textname[$textc++] = mysql_field_name( $result, $FKeins );
  mysql_free_result( $result );

  for( $i=0; $i < $tc; $i++)
  {
    $tabKopf[$i] = $t[0];// Name der 1. M-Tabelle
    if( isset($fDebug) )
      echo "\nt[$i] = $t[$i]<br>";
  }

  // 2. Durchlauf: die Bezeichnungen einlesen
  $Midc = 0;	 // Zaehler ueber die IDs der Treffermenge der	1. M-Tabelle
  // Der Primaerschluessel ist immer das 1. Feld
  $PK = 0;
  $bez = 2; // im 3. Feld einer M-Tabelle steht die bezeichnung

  $res0 = mysql_db_query( $db, "SELECT * FROM $table" );
  if(!$res0 )
  {
    return false;
  }
  $anz = mysql_num_rows( $res0 );
  for( $i=0; $i<$anz;$i++ )      // ueber alle Datensaetze(Result-Set 0)
  {
    $arr = mysql_fetch_row( $res0 );
    $Mid[$Midc++] = $arr[$PK];
    $maxc = $tc-1;		// soviele Tabellen durchforsten
    $offs = $i*$tc + $maxc;
    $zeilen[ $offs ] = $arr[ $bez ];
    if( isset($fDebug) )
      echo "\n[$offs] = $zeilen[$offs]<br>";
    $tabc = 1;
    $maxc--;
    $offs--;
    $fWhile = false;
    while( $maxc )
    {
      $sql = "SELECT * FROM " . $t[$tabc] . " WHERE " . $t[$tabc] . ".ID=";
      if( !$fWhile )
	$sql .= $arr[$FKeins];
      else
	$sql .= $arrm[$FKeins];
      $fWhile = true;
      if( isset($fDebug) )
	echo "\n$sql<br>";
      $result = mysql_db_query( $db, $sql );
      if(!$result)
      {
	return false;
      }
      $arrm = mysql_fetch_row( $result );
			$zeilen[$offs] = $arrm[$bez];
			if( isset($debug) )
			    echo "\n[$offs] = $zeilen[$offs]<br>";
			mysql_free_result( $result );
			$tabc++;
			$maxc--;
			$offs--;
		}
		// Letzte RE-Tabelle auslesen
		$sql = "SELECT * FROM " . $t[$tabc] . " WHERE " . $t[$tabc] . ".ID=";
		if( $fWhile )
			$sql .= $arrm[$FKeins];    
		else
			$sql .= $arr[$FKeins];
		if( isset($fDebug) )
		    echo "\n$sql<br>";
		$result = mysql_db_query( $db, $sql );
		if(!$result)
		{
			return false;
		}
		$arrm = mysql_fetch_row( $result );
		$zeilen[$offs] = $arrm[1];
		if( isset($debug) )
		    echo "\n[$offs] = $zeilen[$offs]<br>";
		    
		mysql_free_result( $result );
	}
	$offs++;
	zeilenSortieren( $offs, count($tabKopf), $zeilen, $Mid );
}
/****************************************************************
 * die Dimension von $tabKopf zeigt an, wieviele Attribute pro 
 * Zeile in der darauffolgenden Listbox nebeneinander
 * dargestellt werden
 ****************************************************************/
/* obsolete
function auslesenEMZuordnung( $db, $sql, $tabKopf, $Mid, $zeilen )
{
	if( $debug )
	    echo "\nEM: $sql<br>";
	//$tabKopf = range(0,-1);
	//$zeilen = range(0,-1);
	//$Mid = range(0,-1);
	$result = mysql_db_query( $db, $sql );
	if(!$result)
	{
		return false;
	}

	$row=mysql_fetch_array( $result, MYSQL_ASSOC );
	$id = true;   // Option Value ist die ID
	$i = 0;
	$j = 0;
	$m = 0;
	$attr = 1;
	$sovielFelder = 3;
	$zaehler = 0;
	foreach( $row as $k=>$elem )
	{
		if( $zaehler >= $sovielFelder )// es wird nur der erste Text nach dem Foreign Key ausgelesen
			break;
		$zaehler++;
		if( $debug )
		    echo "\n$k -- $elem<br>";
		if( $id )
		{// Den PK der M-Tabelle merken
			$Mid[$m++] = $elem;
			$id = false;
			continue;
		}
		$len = strlen($k) - 2;
		$str = substr($k, $len, 2); 
		if( strstr($str, "ID" ) )
		{
			$tabKopf[ $j++ ] = str_replace( "ID", "", $k );
			// Namen der verknuepften Tabelle ermitteln
			$table = str_replace( "ID", "", $k );
			// Anhand des Feldnamens SQL-Statement in die
			// verknuepfte Tabelle basteln
			$arr[ $i ] = "SELECT * FROM " . $table;
			$arr[ $i++ ] .= " WHERE ID = " . $elem;
		}
		else
		{
		// es handelt sich um das Attribut direkt
		   $tabKopf[ $j++ ] = $k;
		    $zeilen[$attr] = $elem;// Luecken lassen fuer die 1-Zuordnung
		    $attr += 2;
		}
	}
	// 2. Schritt: die restlichen Datensaetze auslesen
	while( $row=mysql_fetch_array( $result, MYSQL_ASSOC ) )
	{
		$id = true;   // Option Value ist die ID
		$sovielFelder = 3;
		$zaehler = 0;
		foreach( $row as $k=>$elem )
		{
			if( $zaehler >= $sovielFelder )// es wird nur der erste Text nach dem Foreign Key ausgelesen
				break;
			$zaehler++;
			if( $debug )
			    echo "\n$k -- $elem<br>";
			if( $id )
			{// Den PK der M-Tabelle merken
			    $Mid[$m++] = $elem;
			    $id = false;
			    continue;
			}
			$len = strlen($k) - 2;
			$str = substr($k, $len, 2); 
			if( strstr($str, "ID" ) )
			{
				// Namen der verknuepften Tabelle ermitteln
				$table = str_replace( "ID", "", $k );
				// Anhand des Feldnamens SQL-Statement in die
				// verknuepfte Tabelle basteln
				$arr[ $i ] = "SELECT * FROM " . $table;
				$arr[ $i++ ] .= " WHERE ID = " . $elem;
			}
			else
			{
			// es handelt sich um das Attribut direkt
			   $zeilen[$attr] = $elem;
			   $attr += 2;
			}
		}
	}
	mysql_free_result( $result );
	$anz = count( $arr );
	for( $i=0; $i < $anz; $i++ )
	{
		$result = mysql_db_query( $db, $arr[$i] );	// muss ein eindeutiger Treffer sein
		if(!$result)
		{
			return false;
		}
		$attr = mysql_fetch_row( $result );
		for( $j=0; ;$j++ )// Luecke suchen, weil $zeilen oben
				 //schon mit direkten Attributen versorgt wurde
		     if( !$zeilen[$j] )
		     {
			$zeilen[$j] = $attr[1];		     
			break;
		     }
	}
	mysql_free_result( $result );
}
*/
?>
