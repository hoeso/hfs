<?php
/************ Input **********************************************************
 * zielTabelle	    : in die zu speichernde Tabelle
 * keinInsert		 : es wird kein Datensatz angeboten zum Erfassen
 *****************************************************************************/
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
$debug=false;
if( isset($UniquePK) )
  echo "\n\t<INPUT TYPE='HIDDEN' NAME='UniquePK' VALUE='$UniquePK'>";
if( isset($ID1) and $ID1 )
   echo "\n\t<INPUT TYPE='HIDDEN' NAME='ID1' VALUE='$ID1'>";
if( isset($TabellePK) and $TabellePK )
{
	echo "\n\t<INPUT TYPE='HIDDEN' NAME='TabellePK' VALUE='$TabellePK'>";
	echo "\n\t<INPUT TYPE='HIDDEN' NAME='PK' VALUE='$PK'>";
}
if( isset($speichernID) and $speichernID )// es ist eine Referenz auf die globale Tabelle mitabzuspeichern
{
	echo "\n\t<INPUT TYPE='HIDDEN' NAME='TabelleID' VALUE='$globalTab'>";
	echo "\n\t<INPUT TYPE='HIDDEN' NAME='ID' VALUE='$globalID'>";
}
if( isset($debugPK) and $debugPK )
{
	echo "\n$PKTabelle<br>";
	echo "\n$PK<br>";
}
/*** Tabellenzeile mit den Auswahllisten fuellen ***/
if( !isset($keinInsert) or false == $keinInsert )
{
  ?><tr><?php
}
/***
 * $anzListe wird in ERMsubmit.inc geprueft, ob nur 1 Liste
 * angezeigt wird.
 ***/
$i=0;
$anzListe=0;
/***
 * $anzListeneintrag wird in ERMsubmit.inc geprueft, ob nur 1
 * Listeneintrag angezeigt wird.
 ***/
$anzListeneintrag=0;
// Gestaffelte Select-Treffermenge in Liste stellen
if( !isset($countMULTISL) )
  $countMULTISL=0;
for( $j=0; $j<$countMULTISL; $j++ )
{
  if( !isset($keinInsert) or false == $keinInsert )
  {
    ?><td align=right><?php
  }
  unset($arrID);
  unset($arrZeilen);
  for( $i=0; $i<$countMULTI1SL; $i++ )
  {
    unset($Mid);
    unset($zeilen);
    lesenTabelleMitID( $MySQLDb, $MULTI1SL[$j][$i], $nSpalten, $Mid, $zeilen );
    if( $nSpalten )
    {
      for( $c=0; $c<count($Mid);$c++)
      {
        $fSchonDa = false;
        for( $cc=0;$cc<count($arrID);$cc++)
	  if( $Mid[$c] == $arrID[$cc] )
            $fSchonDa = true;
	if( false == $fSchonDa )
        {
          array_push( $arrID, $Mid[$c] );
          array_push( $arrZeilen, $zeilen[$c] );
        }
      }
    }
  }
  if( $i )
  {
    ergebnisListeMitID( $labelMULTI1SL[$j][$i-1], $arrMULTI1SL[$j][$i-1], $nSpalten, $arrID, $arrZeilen );
    if( !isset($keinInsert) or false == $keinInsert )
      echo "\n\t</font></td>";
  }
  $anzListe += $i;
  $i=0;
  $anzListeneintrag += count($Mid);
}
if( isset($arrSL) )
{
  for( $i=0; $i<count($arrSL); $i++ )
  {
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?><td align=right><?php
    }
    unset($Mid);
    unset($zeilen);
    lesenTabelleMitID( $MySQLDb, $SL[$i], $nSpalten, $Mid, $zeilen );
    if( $debug )
      echo"\nSelect : $SL[$i]; $nSpalten Spalten<br>";
    if( $nSpalten )
    {
      ergebnisListeMitID( $labelSL[$i], $arrSL[$i], $nSpalten, $Mid, $zeilen );
      if( !isset($keinInsert) or false == $keinInsert )
        echo "\n\t</font></td>";
    }
    $anzListeneintrag += count($Mid);
  }
}
$anzListe += $i;
$i=0;
// Reine Entitaeten in Liste stellen
if( isset($arrRE) )
{
  for( $i=0; $i<count($arrRE); $i++ )
  {
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?><td align=right><?php
    }
    $fDatum = lesenRETabelle( $result, $MySQLDb, $arrRE[$i], "" );
    if( $result )
    {
      if( !isset($anzuzeigen) )
        $anzuzeigen=1;
      ListeMitID( $result, $labelRE[$i], $arrRE[$i], $fDatum, $anzuzeigen );
      if( !isset($keinInsert) or false == $keinInsert )
      {
        ?></td><?php
      }
      $anzListeneintrag += mysql_num_rows( $result );
      $succ = mysql_free_result( $result );
    }
  }
}
$anzListe += $i;
// EM-Tabellen in Liste stellen
if( $debug )
{
  $i = count($arrEM);
  echo "\nAnzahl EM-Tabellen = $i<br>";
}
$i=0;
if( isset($arrEM) )
  for( $i=0; $i<count($arrEM); $i++ )
  {
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?><td align=right><?php
    }
    $sql = "SELECT * FROM $arrEM[$i]";
  
    unset($tabKopf);
    unset($Mid);
    unset($zeilen);
    auslesenEMKette( $MySQLDb, $arrEM[$i], $tabKopf, $Mid, $zeilen, $dummy, $dummy );
    if( count($tabKopf) )
    {
      if( $debug )
      {
        $anz = count($Mid);
        echo "\nanz = $anz<br>";
        for( $y=0; $y<count($Mid); $y++ )
          echo "\nMid[$y] = $Mid[$y]<br>";
        $y=0;
        while( $y<count($zeilen) )
        {
          echo "\n";
          for( $z=0; $z < count($tabKopf); $z++, $y++ )
            echo "zeilen[$y] = $zeilen[$y], ";
          echo "<br>";
        }
    }
    ergebnisListeMitID( $labelEM[$i], $arrEM[$i], count($tabKopf), $Mid, $zeilen );
    $anzListeneintrag += count($Mid);
  }
  if( !isset($keinInsert) or false == $keinInsert )
    echo "\n\t</font></td>";
}
$anzListe += $i;
$i=0;
// JE-Tabellen in Liste stellen
if( isset($arrMM) )
  for( $i=0; $i<count($arrMM)-1; $i++ )// schmutzig, weil im letzten
  // $arrMM-Element steht der Name der Zieltabelle
  // damit sie auch im Tabellenkopf auftaucht
  {
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?><td align=right><?php
    }
    $sql = "SELECT * FROM $arrMM[$i]";
    if( $debug )
      echo "\n$sql<br>";
    unset($tabKopf);
    unset($JEid);
    unset($zeilen);
    auslesenZuordnung( $MySQLDb, $sql, $tabKopf, $JEid, $zeilen );
    if( count($tabKopf) )
    {
      if( $debug )
      {
        $anz = count($JEid);
        for( $y=0; $y<count($JEid); $y++ )
          echo "\n$JEid[$y]<br>";
        $y=0;
        while( $y<count($zeilen) )
        {
	  echo "\n";
	  for( $z=0; $z < count($tabKopf); $z++, $y++ )
	    echo "$zeilen[$y] ";
	  echo "<br>";
        }
      }
      ergebnisListeMitID( $labelMM[$i], $arrMM[$i], count($tabKopf), $JEid, $zeilen );
      $anzListeneintrag += count($JEid);
    }
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?></td><?php
    }
}
$anzListe += $i;

// Eingabefelder der Zieltabelle ausgeben
if( isset($arrMM) )
  $zielTabelle=$arrMM[$i];
if( !isset($keinInsert) or false == $keinInsert )
{
  ?><td align=right><?php // bgcolor='#E8E8E8' align='right' nowrap><font size='-2'>";
}
if( $zielTabelle and (!isset($keinInsert) or false == $keinInsert) )
{
  $result = mysql_list_fields( $MySQLDb, $arrMM[$i], $lkid );
  if( false == $result )
  {
    echo"\nFelder der Entit&auml;t $arrMM[$i] k&ouml;nnen nicht gelesen werden.<br>";
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
  /*** HIER KANN MAN DIE KONSTANTEN TESTEN, DIE
   *** WEITER UNTEN ZUR FELDTYP-BESTIMMUNG HERANGEZOGEN
   *** WERDEN KOENNEN
   ***/
  if( isset($_REQUEST["d"]) )
  {
    dEcho( $b_, "type int  : " . MYSQLI_TYPE_LONG );//   3 : ok 
    dEcho( $b_, "type enum : " . MYSQLI_TYPE_ENUM );// 247 : nok
    dEcho( $b_, "flag enum : " . MYSQLI_ENUM_FLAG );// 256 : nok
    dEcho( $b_, "type num  : " . MYSQLI_NUM       );// 247 : nok
    dEcho( $b_, "type datum: " . MYSQLI_TYPE_DATE );//  10 : ok 
  }
  ?><p><?php
  $focusFeld=false;      // Namen des 1. Eingabefeldes speichern in $focusName
  $enumIDX=1;
  if( "5" < $versionPHP[0] )
  {
  $y=-1;
  $anz=0;
  while ($a_=mysqli_fetch_field($result))
  {
    ++$y;
    if( isset($_REQUEST["d"]) )
      dEcho( $b_, "FeldNr: " . $y );
    $anz++; // Anzahl Spalten
    /*** HIER KANN MAN SICH DIE FELDTYP-WERTE ANZEIGEN LASSEN, DIE
     *** WEITER UNTEN ZUR FELDTYP-BESTIMMUNG HERANGEZOGEN
     *** WERDEN MUESSEN
     ***/
    if( isset($_REQUEST["d"]) )
    {
      dEcho( $b_, "Name: " . $a_->name  );
      dEcho( $b_, "Type: " . $a_->type  );
      dEcho( $b_, "Flag: " . $a_->flags );
    }
    $elem = $a_->name;

    // alle Felder ausgeben, welche	nicht auf "ID" enden
    // also keine Verknuepfungen sind
    $len = strlen($elem) - 2;
    $str = substr($elem, $len, 2); 
    if( strstr($str, "ID" ) )
      continue;
    echo "\n";
    ?><li><?php
    $fType = true;
    $feld = $elem;
    if( !isset($keinInsert) or false == $keinInsert )
    {
      echo "\n<label for=\"$elem\">$elem:</label><";
      $strId = $elem;
    }
    $feldFlag = mysql_field_flags( $result, $y );
    if( !isset($keinInsert) or false == $keinInsert )
    {
      if( 254 ==  $a_->type ) // enum
        echo "SELECT ";
      /*** blob wird noch ausgespart
      else if( strstr( $feldFlag, "blob" ) )
        echo "TEXTAREA ";
       ***/
      else
        echo "INPUT ";
    }
    if( !$focusFeld )
      $focusName="$zielTabelle" . "_";
    if( !isset($keinInsert) or false == $keinInsert )
      echo "NAME='$zielTabelle" . "_";
    /*** fortsetzen: ***/
    if( !isset($keinInsert) or false == $keinInsert )
    {// if keinInsert
      if( $fType ) {
        echo "$feldFlag" . "_" . "$feld'";
      if( !$focusFeld )
      {
        $focusName .="$feldFlag" . "_" . "$feld";
        $focusFeld=true;
      }
      /*** statt switch()
      switch( $elem )
      {// switch
       *** if-else if
       ***/
        if( 10 ==  $a_->type )
        {
        //case "date":
          echo " TYPE='TEXT' SIZE=10 VALUE='";
    	      include("eingabeFuellenDatum.prj");
          echo "'></li>";
        //break;
        }
        /*** noch ausgespart: 
        case "real":
          echo " TYPE='TEXT' SIZE=8 VALUE='";
    	      include("vorbelegenReal.prj");
          echo"'>\n</li>\n";
        break;
         ***/
        else if( 254 ==  $a_->type ) // enum - keine passende Konstante gefunden
        {
          echo " SIZE='1'>";
          $strKey=$zielTabelle;
          if( !isset($enumListe["$zielTabelle"]) )
          {
            $strKey .= "_$enumIDX";
            $enumIDX++;
          }
    	  	include("vorbelegenEnum.prj");
          echo "</SELECT></li>";
        }
        /*** noch ausgespart: 
        case "string":
          $feldFlag = mysql_field_flags( $result, $y );
           *** das ist im Vorgaenger else-if schon behandelt:
          if( strstr( $feldFlag, "enum" ) )
          {  
            echo " SIZE='1'>";
            $strKey=$zielTabelle;
            if( !isset($enumListe["$zielTabelle"]) )
            {
              $strKey .= "_$enumIDX";
              $enumIDX++;
            }
    		include("vorbelegenEnum.prj");
            echo "</SELECT></li>";
          }
          else
           ***
          {
            echo " TYPE='TEXT'";
            include("vorbelegenString.prj");
            echo" id=\"$strId\"/></li>";
          }
        break;
        case "time":
          if( "Verzoegerung" == $zielTabelle )
            $val=$Beginn;
          else
    	      {
            $val=date("H:i",time());
    	      }
          echo " TYPE='TEXT' SIZE=8 VALUE='$val'>\n</li>\n";
        break;
        case "blob":
          echo " COLS=86 ROWS=3 WRAP=PHYSICAL>";
          include("vorbelegenBlob.prj");
          ?></TEXTAREA></LI><?php
        break;
        ***/
        else
        {
        //default:
          echo " TYPE='TEXT' >\n</li>\n";
          if( $debug ) echo"\nfeldFlag: $feldFlag. elem: $elem<br>";

        //break;
        }
      }
    }
  }
  }
  else
  {
    $anz = mysql_num_fields( $result );
    if( isset($_REQUEST["d"]) )
    {
      dEcho( $b_, "Anzahl Felder: " . $anz );
    }
for( $i=0; $i<$anz; $i++ )
{
  $obj = mysql_fetch_field( $result, $i );

  $fType = false;
  foreach( $obj as $k=>$elem )
  {
    switch( $k )
    {
      case "name":
        // alle Felder ausgeben, welche	nicht auf "ID" enden
        // also keine Verknuepfungen sind
        $len = strlen($elem) - 2;
        $str = substr($elem, $len, 2); 
        if( strstr($str, "ID" ) )
          break;
        $fType = true;
        $feld = $elem;
        // siehe Datei mapSpaltennamen.inc:
        if( isset($SpaltenAlias) and isset($key[$SpaltenAlias]) )
          $str=$key[$SpaltenAlias];
        if( !isset($keinInsert) or false == $keinInsert )
        {
          if( $elem==$str )
          {
            if( isset($SpaltenAlias) and isset($map[$SpaltenAlias]) and $map[$SpaltenAlias] )
              echo "\n$map[$SpaltenAlias]: <";
            else
              echo "\n$elem: <";
          }
          else
            echo "\n$elem: <";
        }
        $feldFlag = mysql_field_flags( $result, $i );
        if( !isset($keinInsert) or false == $keinInsert )
        {
          if( strstr( $feldFlag, "enum" ) )
            echo "SELECT ";
          else if( strstr( $feldFlag, "blob" ) )
            echo "TEXTAREA ";
          else
            echo "INPUT ";
        }
        if( !$focusFeld )
          $focusName="$zielTabelle" . "_";
        if( !isset($keinInsert) or false == $keinInsert )
          echo "NAME='$zielTabelle" . "_";
        if( "SchlussrechnungAm" == $elem or "AbnahmeAm" == $elem or "Erteilung" == $elem )
          $fSchlussrechnung=true;
      break;
      case "type":
        if( !isset($keinInsert) or false == $keinInsert )
        {// if keinInsert
          if( $fType ) {
            echo "$elem" . "_" . "$feld'";
          if( !$focusFeld )
          {
            $focusName .="$elem" . "_" . "$feld";
            $focusFeld=true;
          }
          switch( $elem )
          {// switch
            case "date":
	      /*** wg. FF Quantum: solange nicht auf HTML5 umgestellt ist
              echo " TYPE='date' VALUE='";
	       ***/
              echo " TYPE='text' VALUE='";
	      include("eingabeFuellenDatum.prj");
              echo "'><br>";
            break;
            case "int":
              echo " TYPE='TEXT' SIZE=8 VALUE='";
	      include("vorbelegenInt.prj");
              echo"'><br>";
            break;
            case "real":
              echo " TYPE='TEXT' SIZE=8 VALUE='";
	      include("vorbelegenReal.prj");
              echo"'><br>";
            break;
            case "string":
              $feldFlag = mysql_field_flags( $result, $i );
              if( strstr( $feldFlag, "enum" ) )
              {
	        echo " id='$feld'"; // fuer Plausi in ERMListenfuellen.prj
                echo " SIZE='1'>";
                $strKey=$zielTabelle;
                if( !isset($enumListe["$zielTabelle"]) )
                {
                  $strKey .= "_$enumIDX";
                  $enumIDX++;
                }
  		include("vorbelegenEnum.prj");
                echo "</SELECT><br>";
              }
              else
              {
                echo " TYPE='TEXT'";
                include("vorbelegenString.prj");
                echo"><br>";
              }
            break;
            case "time":
              if( "Verzoegerung" == $zielTabelle )
                $val=$Beginn;
              else
	      {
                $val=date("H:i",time());
	      }
              echo " TYPE='TEXT' SIZE=8 VALUE='$val'><br>";
            break;
            case "blob":
	      include("textarea.prj");
              ?> COLS=86 ROWS=<?php
	      if( isset($_E['textzeilen']) )
	        echo $_E['textzeilen'];
	      else
	      {
	        ?>3<?php
	      }
	      ?> WRAP=PHYSICAL><?php
              include("vorbelegenBlob.prj");
?></TEXTAREA><BR><?php
            break;
            case "datetime":
              echo " TYPE='TEXT' VALUE='";
	      include("eingabeFuellenDatum.prj");
              echo "'><br>";
            break;
            default:
              echo " TYPE='TEXT' ><br>";
              if( $debug ) echo"\nfeldFlag: $feldFlag. elem: $elem<br>";

            break;
          }
        }
      }
      break;
    }
  }
  }
  }
echo "\n";
?></ul></fieldset><?php
if( !isset($keinInsert) or false == $keinInsert )
{
  if( $zielTabelle )// Speichern-Knopf mittig in unterste Tabellenzeile ausgeben
  {
     ?></td><?php
     echo "\n\t<tr><td colspan=$anz>";
  }
}
return;
  //$anz = mysql_num_fields( $result );
  $anz = $result->num_rows;
  if( $debug )
    echo "\nFeldanzahl '$arrMM[$i]': $anz<br>";
  $a = mysqli_fetch_fields( $result );
  foreach( $a as $k=>$elem )
    echo $k . " -- " . $elem . "<br>";
  exit;
  echo "\n"; // damit Zeilenumbruch im Quelltext
  ?><fieldset><legend><span><?php echo $zielTabelle; ?>, neuer Eintrag:</span></legend><?php
  echo "\n";
  ?><ul><?php
  echo "\n";
  for( $i=0; $i<$anz; $i++ )
  {
    $obj = mysql_fetch_field( $result, $i );
    $fType = false;
    foreach( $obj as $k=>$elem )
    {
      switch( $k )
      {
        case "name":
          // alle Felder ausgeben, welche	nicht auf "ID" enden
          // also keine Verknuepfungen sind
          $len = strlen($elem) - 2;
          $str = substr($elem, $len, 2); 
          if( strstr($str, "ID" ) )
            break;
          echo "\n";
          ?><li><?php
          $fType = true;
          $feld = $elem;
          // siehe Datei mapSpaltennamen.inc:
          if( isset($SpaltenAlias) and isset($key[$SpaltenAlias]) )
            $str=$key[$SpaltenAlias];
          if( !isset($keinInsert) or false == $keinInsert )
          {
            if( $elem==$str )
            {
              if( $map[$SpaltenAlias] )
                echo "\n<label for=\"$map[$SpaltenAlias]\">$map[$SpaltenAlias]:</label><";
              else
                echo "\n<label for=\"$elem\">$elem:</label><";
            }
            else
              echo "\n<label for=\"$elem\">$elem:</label><";
            $strId = $elem;
          }
          $feldFlag = mysql_field_flags( $result, $i );
          if( !isset($keinInsert) or false == $keinInsert )
          {
            if( strstr( $feldFlag, "enum" ) )
              echo "SELECT ";
            else if( strstr( $feldFlag, "blob" ) )
              echo "TEXTAREA ";
            else
              echo "INPUT ";
          }
          if( !$focusFeld )
            $focusName="$zielTabelle" . "_";
          if( !isset($keinInsert) or false == $keinInsert )
            echo "NAME='$zielTabelle" . "_";
          if( "SchlussrechnungAm" == $elem or "AbnahmeAm" == $elem or "Erteilung" == $elem )
            $fSchlussrechnung=true;
        break;
        case "type":
          if( !isset($keinInsert) or false == $keinInsert )
          {// if keinInsert
            if( $fType ) {
              echo "$elem" . "_" . "$feld'";
            if( !$focusFeld )
            {
              $focusName .="$elem" . "_" . "$feld";
              $focusFeld=true;
            }
            switch( $elem )
            {// switch
              case "date":
                echo " TYPE='TEXT' SIZE=10 VALUE='";
      		      include("eingabeFuellenDatum.prj");
                echo "'></li>";
              break;
              case "real":
                echo " TYPE='TEXT' SIZE=8 VALUE='";
      		      include("vorbelegenReal.prj");
                echo"'>\n</li>\n";
              break;
              case "string":
                $feldFlag = mysql_field_flags( $result, $i );
                if( strstr( $feldFlag, "enum" ) )
                {  
                  echo " SIZE='1'>";
                  $strKey=$zielTabelle;
                  if( !isset($enumListe["$zielTabelle"]) )
                  {
                    $strKey .= "_$enumIDX";
                    $enumIDX++;
                  }
      			include("vorbelegenEnum.prj");
                  echo "</SELECT></li>";
                }
                else
                {
                  echo " TYPE='TEXT'";
                  include("vorbelegenString.prj");
                  echo" id=\"$strId\"/></li>";
                }
              break;
              case "time":
                if( "Verzoegerung" == $zielTabelle )
                  $val=$Beginn;
                else
      		      {
                  $val=date("H:i",time());
      		      }
                echo " TYPE='TEXT' SIZE=8 VALUE='$val'>\n</li>\n";
              break;
              case "blob":
                echo " COLS=86 ROWS=3 WRAP=PHYSICAL>";
                include("vorbelegenBlob.prj");
?></TEXTAREA></LI><?php
              break;
              default:
                echo " TYPE='TEXT' >\n</li>\n";
                if( $debug ) echo"\nfeldFlag: $feldFlag. elem: $elem<br>";

              break;
            }
          }
        }
        break;
      }
    }
  }
}
echo "\n";
?></ul></fieldset><?php
if( !isset($keinInsert) or false == $keinInsert )
{
  if( $zielTabelle )// Speichern-Knopf mittig in unterste Tabellenzeile ausgeben
  {
     ?></td><?php
     echo "\n\t<tr><td colspan=$anz>";
  }
}
?>
