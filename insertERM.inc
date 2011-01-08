<?
/**********************************************
 * Übergabe von Primaerschluesseln aus reinen Entitaeten
 * und JE Tabellen und eigenen Attributen zum
 * Einfuegen.
 * Uebergabe-Parameter:
 * zielTabelle		Name der Tabelle, in die eingefuegt werden soll
 * TabelleSL[1-4]	Namen von bis zu 4 Tabellen, deren Primaerschluessel
 *                      in das Feld {TabelleSL[1-4]}ID eingetragen werden soll
 * TabelleRE[1-5]	Namen von bis zu 5 Tabellen, deren Primaerschluessel
 *                      in das Feld {TabelleRE[1-5]}ID eingetragen werden soll
 * TabelleMM[1-3]	Namen von bis zu 3 JE-Tabellen, deren Primaerschluessel
 *                      in das Feld {TabelleMM[1-3]}ID eingetragen
 *			 werden soll
 * SELECTRE[1-5]	 Die bis zu 5 Primaerschluessel der RE Tabellen
 * SELECTMM[1-3]	 Die bis zu 3 Primaerschluessel der JE
 *			  Tabellen
 * {zielTabelle}.{Feldtyp}.{Feldname}	Eine Liste von Attributen der
 *					Zieltabelle mit Angabe des
 *					 Feldtyps und -namens
 * es wird anhand der uebergebenen Primaerschluessel
 * geprüft, ob der Eintrag bereits existiert
 * falls noch nicht, wird der Datensatz angelegt
 ***********************************************/
$debug = 0;
if( isset($SELECTSL1) and $SELECTSL1 && !isset($backupSELECTSL1) )
    $backupSELECTSL1=$SELECTSL1;
$debugPK=false;

$HTTP_POST_VARS = $_POST;
if( !isset( $HTTP_POST_VARS ) )
{
	echo "Die Uebergabedaten k&ouml;nnen nicht gelesen werden<br>";
	echo "Verst&auml;ndigen Sie ihren Systemadministrator<br>";
	echo "<ul>M&ouml;gliche Fehlerursachen";
	echo "<li>Die Formulardaten wurden nicht mit METHOD='POST' gesendet";
	echo "<ul>";
	exit;
}
reset( $HTTP_POST_VARS );

// erst mal pruefen, ob die Verknuepfung vielleicht schon existiert
// weil sie muss einmalig sein

unset( $arrPK );

foreach( $HTTP_POST_VARS as $k=>$elem )
{
	switch( $k )
	{
		case "TabelleID":
		     $keyID = $elem . "ID";
		     break;
		case "ID":
		     $arrPK[ $keyID ] = $elem;
		     break;
		case "TabellePK":
		     $keyPK = $elem . "ID";
		     break;
		case "PK":
		     $arrPK[ $keyPK ] = $elem;
		     break;
		case "TabelleSL1":
		     $keySL1 = $elem . "ID";
		     break;
		case "SELECTSL1":
		     $arrPK[ $keySL1 ] = $elem;
		     break;
		case "TabelleSL2":
		     $keySL2 = $elem . "ID";
		     break;
		case "SELECTSL2":
		     $arrPK[ $keySL2 ] = $elem;
		     break;
		case "TabelleSL3":
		     $keySL3 = $elem . "ID";
		     break;
		case "SELECTSL3":
		     $arrPK[ $keySL3 ] = $elem;
		     break;
		case "TabelleSL4":
		     $keySL4 = $elem . "ID";
		     break;
		case "SELECTSL4":
		     $arrPK[ $keySL4 ] = $elem;
		     break;
		case "TabelleRE1":
		     $keyRE1 = $elem . "ID";
		     break;
		case "SELECTRE1":
		     $arrPK[ $keyRE1 ] = $elem;
		     break;
		case "TabelleRE2":
		     $keyRE2 = $elem . "ID";
		     break;
		case "SELECTRE2":
		     $arrPK[ $keyRE2 ] = $elem;
		     break;
		case "TabelleRE3":
		     $keyRE3 = $elem . "ID";
		     break;
		case "SELECTRE3":
		     $arrPK[ $keyRE3 ] = $elem;
		     break;
		case "TabelleRE4":
		     $keyRE4 = $elem . "ID";
		     break;
		case "SELECTRE4":
		     $arrPK[ $keyRE4 ] = $elem;
		     break;
		case "TabelleRE5":
		     $keyRE5 = $elem . "ID";
		     break;
		case "SELECTRE5":
		     $arrPK[ $keyRE5 ] = $elem;
		     break;
		case "TabelleEM1":
		     $keyEM1 = $elem . "ID";
		     break;
		case "SELECTEM1":
		     $arrPK[ $keyEM1 ] = $elem;
		     break;
		case "TabelleEM2":
		     $keyEM2 = $elem . "ID";
		     break;
		case "SELECTEM2":
		     $arrPK[ $keyEM2 ] = $elem;
		     break;
		case "TabelleEM3":
		     $keyEM3 = $elem . "ID";
		     break;
		case "SELECTEM3":
		     $arrPK[ $keyEM3 ] = $elem;
		     break;
		case "TabelleMM1":
		     $keyMM1 = $elem . "ID";
		     break;
		case "SELECTMM1":
		     $arrPK[ $keyMM1 ] = $elem;
		     break;
		case "TabelleMM2":
		     $keyMM2 = $elem . "ID";
		     break;
		case "SELECTMM2":
		     $arrPK[ $keyMM2 ] = $elem;
		     break;
		case "TabelleMM3":
		     $keyMM3 = $elem . "ID";
		     break;
		case "SELECTMM3":
		     $arrPK[ $keyMM3 ] = $elem;
		     break;
		case "UniquePK":
		     // Das Flag ignorieren
		     break;
		case "ID1":
		     // Die ID der 1. RE-Tabelle (= Filter) ignorieren
		     break;
		case "zielTabelle":
		     $table = $elem;
		     break;
		case "zielT":	// Manchmal heisst sie auch so
		     $zielTabelle=$elem;
		     $table = $elem;
		     break;
		default;
			$str = substr( $k, 0, 6 );
			if( !strcmp( "hidden", $str ) )
			    break;
			$arrAttr[ $k ] = $elem;
			break;
	}
	// case zielTabelle.switch typ 
}
if( $debug )
{
	if( count($arrPK ) )
		foreach( $arrPK as $k=>$elem )
		{
			echo "\nPK: $k -- $elem<br>";
		}
	if( count($arrAttr ) )
		foreach( $arrAttr as $k=>$elem )
		{
			echo "\nAttr: $k -- $elem<br>";
		}
}
if( $debugPK )
{
	echo "\n$PKTabelle<br>";
	echo "\n$PK<br>";
}

$nTreffer = 0;

if( isset($UniquePK) and $UniquePK )
{
	$succ = suchenMitPK( $MySQLDb, $table, $arrPK, $nTreffer, $globalID, $arr );
	if( !$succ )
	{
		echo "\nEs ist ein Fehler aufgetreten beim Ueberpr&uuml;fen,";
		echo "ob der Datensatz in der Tabelle $table schon vorhanden ist<br>";
		exit;
	}
	if( $nTreffer > 0 )
	{
		if( $debug )
		    echo "\n$sql<br>";
		echo "\nDieser Eintrag existiert bereits: ";
		for( $i=0; $i<count($arr); $i++ )
			echo "\n $arr[$i]";
		echo "\n<br>";
		$autoID=$globalID;
	}
}
if( $debug )
    if( count($arrAttr) )
        foreach( $arrAttr as $k=>$elem )
	{
		echo "\nAttr: $k -- $elem<br>";
	}
if( $debug )
	echo "\n$sql<br>";
if( !$nTreffer )
{

// Bei bereits zugestellter Gewerk-Gutschrift den Insert blocken:
      if( $table=="AuftragExtraArbeit" )
      {
	 foreach( $arrPK as $k=>$elem )
	 {
	    if( "AuftragID"==$k )
               $auid=$elem;
	    else if( "GewerkID"==$k )
	       $gwid=$elem;
	 }
	 if( $gwid && $auid )
	 {
	    unset($arr);
	    $arr[0]=0;   // Nummer
	    $arr[1]=1;   // NachunternehmerID
	    gibFelderArray( $MySQLDb, "SELECT Nummer, NachunternehmerID FROM PaketAuftrag, Gutschrift, GutschriftJournal WHERE PaketAuftrag.AuftragID=$auid AND PaketAuftrag.GewerkID=$gwid AND Gutschrift.PaketAuftragID=PaketAuftrag.ID AND GutschriftJournal.GutschriftID=Gutschrift.ID AND GutschriftJournal.zugestellt='ja'", $arr );
	    if( $arr[0] )
	    {
	       echo"\n<center><h3>Auftrag ist beendet</h3>";
	       $sql="SELECT Bezeichnung FROM Nachunternehmer WHERE ID=$arr[1]";
	       $name = gibFeld( $MySQLDb, $sql, 0 );
	       echo"\n<h4>Die Gutschrift <em>$arr[0]</em> wurde bereits an <em>$name</em> zugestellt. Der Auftrag kann nur noch &uuml;ber eine Zusatzgutschrift erg&auml;nzt werden, nachdem der Nachunternehmer gegen die Gutschrift Widerspruch einlegt hat</h4>";
	       exit;
	    }
	 }
      }


	if( !isset($UniquePK) )
	  $UniquePK="";
	$gespeichert = speichernPKsUndAttr( $lkid, $MySQLDb, $table,$arrPK, $arrAttr, $UniquePK, $sql, $autoID );
    if( !$gespeichert )
    {
	$AusgabeUnterdruecken=true;
	reagierenAufSQLFehler( $lkid, $sql, $PKViolation );
	if( $PKViolation )
	{
	}
	if( 0 == $autoID )
		exit;
	if( $table == $globalTab )
	    $globalID=$autoID;
	}
}
if( $gespeichert )
{
	echo "\nDer Eintrag wurde gespeichert";

	$sql = "SELECT LAST_INSERT_ID() FROM " . $zielTabelle;
	$result = mysql_db_query( $MySQLDb, $sql );
	$arr = mysql_fetch_row( $result );
	if( isset($globalTab) and $table == $globalTab )//nicht, wenn Aufruf aus Administration
	{
		$globalID=$arr[0];
	}
	$autoID=$arr[0];
	mysql_free_result( $result );
}

?>
