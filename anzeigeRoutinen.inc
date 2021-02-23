<?php
/******** Formular-Funktionen ************************************************/
function setFieldDate($attr, &$fHTML5)
{
  $fHTML5 = false;
  if( isset( $_SERVER['HTTP_USER_AGENT'] ) )
  {
    $signature = "Firefox/";
    $ver = strstr( $_SERVER['HTTP_USER_AGENT'], $signature );
  	if( $ver )
  	{
  	  $a_ = explode( '/', $ver );
  	  if( 55 < $a_[1] )
          {
            $fHTML5 = true;
            return $attr; // HTML5, passt.
          }
  	}
  }
  $arr = explode( "-", $attr );
  if( 4 == strlen( $arr[0] ) )
    $datum = "$arr[2].$arr[1].$arr[0]";
  else
    $datum = $attr;
  return $datum;
}
function formularBeginnen($action,$extra)
{
  global $_E;
  echo "\n<FORM $extra ACTION='$action";
  if( isset($_E['navi']) )
    echo "&navi=" . $_E['navi'];
  echo "' METHOD='POST'>\n";
}
function formularKnopf($value,$name='easy')
{
  echo "\n<INPUT TYPE='SUBMIT' VALUE='$value' NAME='$name'>\n";
}
function hiddenFeldSchreiben( $name, $value )
{
  echo_("\n\t<INPUT TYPE='HIDDEN' NAME='$name' VALUE='$value'>\n");
}
function formularAuswahlfeldSchreiben( $text, $strTextAlign, $typ, $fChecked, $name, $value )
{
  if( $strTextAlign == "links" )
      echo "\n\t$text ";
  echo "<INPUT TYPE=$typ";
  if( $fChecked )
      echo " checked";
  echo " NAME=$name VALUE=\"$value\">";
  if( $strTextAlign == "rechts" )
      echo " $text";
}
function formularBeenden()
{
  echo"\n</FORM>\n";
}
/******** Tabellen-Funktionen ************************************************/
function tabelleBeginnen( $caption = "" )
{
  global $fAnzeigeUnterdruecken;
  if( $fAnzeigeUnterdruecken )
    return;
  ?><table><caption><?php if( isset($caption) and ("ohne submit Knopf" != $caption) ) echo $caption;?></caption><?php
  return true;
}
function tabelleBeenden()
{
  ?></table><?php
  echo "\n";
}
function tabellenZeileBeginnen()
{
  ?><tr><?php
  echo "\n";
}
function tabellenZeileBeenden()
{
  ?></tr><?php
  echo "\n";
}
function tabellenZelleBeginnen()
{
  ?><td><?php
}
function tabellenZelleBeenden()
{
  ?></td><?php
  echo "\n";
}
function zaehlenAttributSpalten( $spaltenName, &$cSpalten )
{
  $cSpalten = 0;
  $anz = count( $spaltenName );
  for( $i=1; $i < $anz; $i++ )
    if( false == istForeignKeyName( $spaltenName[$i] ) )
      $cSpalten++;
}
function headerFooter( $mark, $spaltenName, $auchID, &$cSpalten, $sql, $zielTabelle, $aColspan )
{
  global $unterdrueckteSpalte;
  global $_E;
  global  $proj;
  global  $pw;

  if( isset($_E['ident']) )
    $gruppenStaerke = $_E['ident'];
  else
    $gruppenStaerke = 1;
  $str=str_replace( " ", "%20", $sql );
  $str=str_replace( "&uuml;", "%FC", $str );
  $cSpalten = 0;
  $anz = count( $spaltenName );
  echo "<$mark>";
  ?><tr><?php
  if( $auchID )
  {
    ?><th></th><?php
  }
  for( $i=1; $i < $anz; $i++ )
  {
    if( false == istForeignKeyName( $spaltenName[$i] ) )
    {
      $fUnterdruecken=false;
      if( isset($unterdrueckteSpalte) )
        for($c=0;$c<count($unterdrueckteSpalte);$c++)
          if( $unterdrueckteSpalte[$c] == $spaltenName[$i] )
            $fUnterdruecken=true;
      if( false == $fUnterdruecken )
      {
        ?><th<?php
        $j=$i-1;
        if( isset( $aColspan[$j] ) and $aColspan[$j] )
           echo_(" colspan=$aColspan[$j]");
        ?>><?php
        if( !isset($Bezug) )
          $bzg = "";
        else
          $bzg = "&Bezug=$Bezug";
        /*echo_("<A HREF=\"./eiZu.php?wZu=zeigendDruckansicht&zielTabelle=$zielTabelle&sql=$str$bzg&bgcolor=white&gruppenStaerke=$gruppenStaerke&$proj&orderBy=$spaltenName[$i]&desc=false\">*/echo_($spaltenName[$i]);/*</A>");*/
        ?></th><?php
        $cSpalten++;
      }
    }
  }
  if( !$zielTabelle )  // Hier soll keine Druckansicht angeboten werden, z.B. in der Preisansicht
  {
    ?></tr><?php
  }
  else if( "ohne submit Knopf" <> $zielTabelle )
  {
    $Bezug="";
    ?><th><?php
//    echo_("\n<FORM ACTION=\"./eiZu.php?wZu=zeigendDruckansicht&zielTabelle=$zielTabelle&Bezug=$Bezug&bgcolor=white&gruppenStaerke=$gruppenStaerke&$proj\" METHOD=POST>\n<INPUT TYPE=HIDDEN NAME=sql VALUE=\"$sql\">\n<INPUT TYPE=SUBMIT VALUE=Druckansicht>\n</FORM>");
//    echo_("\n<A HREF=\"./eiZu.php?wZu=zeigendDruckansicht&zielTabelle=$zielTabelle&sql=$str&Bezug=$Bezug&bgcolor=white&gruppenStaerke=$gruppenStaerke&$proj\">Druckansicht</A>");
    ?></th></tr><?php
  }
  echo "</$mark>";
}
function ausgebenAlsTabellenkopf( $spaltenName, $auchID, &$cSpalten, $sql, $zielTabelle, $aColspan, $f = true )
{
  if( false == $f )
    return; // Ohne Spalten-Namen
  headerFooter( "thead", $spaltenName, $auchID, $cSpalten, $sql, $zielTabelle, $aColspan );
  headerFooter( "tfoot", $spaltenName, $auchID, $cSpalten, $sql, $zielTabelle, $aColspan );
}
function ausgebenAlsTabellenzeile( $row, $auchID, &$fChecked, $spalte, $globalID, $arrFeldTyp, $table, $ActionSuffix, $aColspan, &$recID )
{
global $unterdrueckteSpalte;
global $gruppe;
global $_E;
global $Summenwert;
global $ID1;
global $proj;
global $pw;
$arrNichtLoeschen=array (
  "ohne submit Knopf",
  "vmKursort",
  "mapDenAushang"
);
$mapAushang["flaechengestuft"]="qm";
$mapAushang["pro lfm"]="lfm";
$mapAushang["pro qm"]="qm";
$mapAushang["pro Stück"]="Stück";
$mapAushang["Sockel plus Menge"]="qm";
$mapAushang["<"]="qm";
$mapAushang["<="]="qm";

  if( isset($_E['ident']) )
    $gruppenStaerke = $_E['ident'];
  else
    $gruppenStaerke = 1;

  $istKeineID = false;
  $i=0;
  $fSubmit=true;
  if( !$table )
      $fSubmit=false;
  foreach( $arrNichtLoeschen as $k )
     if( 0 == strcmp( $k, $table ) )
         $fSubmit = false;
  $i=0;
  foreach( $row as $elem )
  {
    if( $istKeineID )
    {
      if( $i <= $gruppenStaerke )
      {
          if( isset($vgl) )
            $vgl .= $elem;
          else
            $vgl = $elem;
      }
    }
    else
      $istKeineID = true;
    $i++;
  }
  $istKeineID = false;
  $i=0;
  foreach( $row as $elem )
  {
    if( $auchID )
    {
      $fSubmit=false;
      $auchID = false;
      ?><td><INPUT TYPE='RADIO' NAME='PK' VALUE=<?php
      echo_("'$elem'");
      if( !$fChecked )
      {
        if( !$globalID )
        {
          ?> CHECKED<?php
          $fChecked = true;
        }
        if( $globalID == $elem )
        {
          ?> CHECKED<?php
          $fChecked = true;
        }
      }
      ?><img src='icons/zwischenPfeil.gif'><?php
      ?><input type=image src='imagesquit.gif'><?php
      ?></td><?php
    }
    if( $istKeineID )
    {
      if( false == istForeignKeyName( $spalte[$i] ) )
      {
        $fUnterdruecken=false;
	if( isset($unterdrueckteSpalte) )
          for($c=0;$c<count($unterdrueckteSpalte);$c++)
            if( $unterdrueckteSpalte[$c] == $spalte[$i] )
              $fUnterdruecken=true;
        if( false == $fUnterdruecken )
        {
          if( isset($arrFeldTyp[$i]) and 'date' == $arrFeldTyp[$i] )
          {
            $arr = explode( "-", $elem );
            if( 4 == strlen( $arr[0] ) )
                $elem = "$arr[2].$arr[1].$arr[0]";
          }
          if( strstr( $spalte[$i], "Euro" ) )
          {
             $align="align=right";
             $Summenwert += $elem;
             $elem = number_format($elem,'2',',','.');
          }
          ?><td <?php
          $j=$i-1;
          if( isset( $aColspan[$j] ) )
            echo_(" colspan=$aColspan[$j]");
          if( !isset($align) )
            $align="";
          echo_("$align>");
          if( strstr( $table, "mapDenAushang" ) )
              if( isset($mapAushang[$elem]) )
            $elem=$mapAushang[$elem];
          if( !isset($vgl) )
            $vgl="";
          if( $gruppe <> $vgl || $i > $gruppenStaerke )
              echo_("$elem</td>");
        }
      }
    }
    else
    {
      $istKeineID = true;
      if( $fSubmit )
      {
      $str = "./mn.php?mn=3653&a=$table&$proj";
      if( $ActionSuffix )
          $str .= $ActionSuffix;
      formularBeginnen($str, "");
      hiddenFeldSchreiben( "ID", $elem );
      if( $ID1 )
        hiddenFeldSchreiben( "ID1", $ID1 );
      if( isset($_REQUEST['d']) )
        hiddenFeldSchreiben( "d", 1 );
      }
    }
    if( 0 == $i )
      $recID=$elem;
    $i++;
  }
  if( $fSubmit )
  {
    ?><td><?php echo "\n";
    ?><input type=image src='icons/del.gif' name='delete'>
    </td>
    </FORM><?php
  }
  if( !isset($vgl) )
    $vgl="";
  if( $gruppe <> $vgl )
     $gruppe = $vgl;
}

function ausgebenAlsTabellenzeileZumAendern( $row, $auchID, &$fChecked, $arrFeldTyp, $arrFeldFlag, $arrFeldName, $table, $ActionSuffix, $iFarbReihe=0 )
{
  $arrNichtLoeschen=array (
  "GegenkontoNachunternehmer",
  "Gutschrift",
  "vmKursort",
  );
  include( "toggleYesNo.prj" );
  global $WohnungID;
  global $rootTabelle;
  global $gruppe;
  global $_E;
  global $Kind;
  global $MySQLDb;
  global $ID1;
  global $fPopup;
  global $fKeinUpdate;
  global $fKeinDelete;
  global $proj;
  global $pw;
  global $gfaerbteSpoidn;

  if( isset($_E['ident']) )
    $gruppenStaerke = $_E['ident'];
  else
    $gruppenStaerke = 1;

  if( isset( $gfaerbteSpoidn[$table] ) )
  {
    $zuFaerbendeCols = $gfaerbteSpoidn[$table][0];
    $faerbung = $gfaerbteSpoidn[$table][1];
  }
  else
  {
    $zuFaerbendeCols = 0;
  }

  $istKeineID = false;
  $i=0;
  // Gruppenstaerke - feld ermitteln:
  foreach( $row as $elem )
  {
    if( $istKeineID )
    {
      if( $i <= $gruppenStaerke )
      {
        if( !isset($vgl) )
          $vgl="";
        $vgl .= $elem;
      }
    }
    else
      $istKeineID = true;
   $i++;
  }

  $istKeineID = false;
  $i=0;
  $recID=0;

  foreach( $row as $elem )
  {
    if( !$i )
    {
      // Task Aktennotiz: hier Flag setzen, wenn eine Farb-Bedingung erfuellt ist.
      // dann im Block oben farblich unterlegen.
      $ident=$elem;
      if( $iFarbReihe == $ident )
        $fAnmalen = true;
      include("highlightRow.prj");
    }
    if( $auchID )
    {
      $auchID = false;
      ?><td><input type='radio' name='PK' value=<?php
      echo "'$elem'";
      if( !$fChecked )
      {
        if( !$globalID )
        {
          ?> checked<?php
          $fChecked = true;
        }
        if( $globalID == $elem )
        {
          ?> checked<?php
          $fChecked = true;
        }
      }
      ?><img src='icons/zwischenPfeil.gif'><input type=image src='icons/quit.gif'></td><?php
    }
    if( $istKeineID )
    {
      if( isset($arrFeldTyp[$i]) && 'date' == $arrFeldTyp[$i] )
      {
        $arr = explode( "-", $elem );
        if( 4 == strlen( $arr[0] ) )
          $elem = "$arr[2].$arr[1].$arr[0]";
      }
      else if( isset($arrFeldTyp[$i]) && 'time' == $arrFeldTyp[$i] )
      {
        $arr = explode( ":", $elem );
        $elem = "$arr[0]:$arr[1]";
      }
      //include("anzeigeRoutinen.prj");
      if( isset( $fTooltip ) )
        ;// $farbe ist bereits gesetzt
      else if( isset( $fAnmalen ) )
        //$farbe = 'lightblue';
	//$farbe = '#A4A4A4'; // grau
	$farbe = '#DDDDDD'; // hell-grau
      else if( $zuFaerbendeCols && $zuFaerbendeCols >= $i )
        $farbe = $faerbung;
      ?><td<?php
      if( isset($farbe) )
      {
        ?> bgcolor=<?php
        echo $farbe;
      }
      ?>><?php
      if( isset($arrFeldName[$i]) )
      {
        $key=$arrFeldName[$i] . "_" . $table;
        if( isset($toggleYesNo["$key"]) && strstr( $arrFeldFlag[$i], 'enum' ) && strstr( $toggleYesNo["$key"], $elem ) )
        {
          $str = "<A HREF=\"./mn.php?mn=3151&ID=$ident&feld=$arrFeldName[$i]&wert=$elem&table=$table&$proj";
          if( isset($_REQUEST) and isset($_REQUEST["yyR"]) )
            $str .= "&yyR=$_REQUEST[yyR]";
          echo $str;
          echo"\" title=\"$arrFeldName[$i]";
          echo"\">";
          $fAnkern=true;
        }
      }
      if( !isset($vgl) )
        $vgl="";
      if( $gruppe <> $vgl || $i > $gruppenStaerke )
      {
        if( isset( $fragment ) )
          echo"<A NAME='$fragment'>";
        echo $elem;
        if( isset( $fragment ) )
        {
          echo"</A>";
          unset( $fragment );
        }
      }
      if( isset($key) && isset($toggleYesNo["$key"]) && strstr( $arrFeldFlag[$i], 'enum' ) && strstr( $toggleYesNo["$key"], $elem ) )
      {
      }
      if( isset($fAnkern) and true == $fAnkern )
        echo "</A>";
      ?></td><?php
    }
    else
    {
      $istKeineID = true;
      $str = "./mn.php?mn=3653&a=$table&$proj";
      if( $ActionSuffix )
        $str .= $ActionSuffix;
      formularBeginnen($str, "");
      hiddenFeldSchreiben( "ID", $elem );
      $fragment=$elem;
      if( $ID1 )
        hiddenFeldSchreiben( "ID1", $ID1 );
      if( isset($_REQUEST['d']) )
        hiddenFeldSchreiben( "d", 1 );
      $recID=$elem;
    }
    $i++;
  }
  if( !isset($vgl) )
    $vgl="";
  if( $gruppe <> $vgl )
    $gruppe = $vgl;
  ?><td><?php

  global $fPeek;
  include("lastExitBrooklyn.prj");

  if( !isset($gutschriftZugestellt) && !$fPopup && !isset($_E['bleistift']) )
  {
    if(0)
    {
      ?><input type=image src='icons/edit.gif' name='update'><?php
    }
    else if( isset( $recID) )
    {
      ?><img src="icons/iconmonstr-pencil-thin-16.png" alt="Edit ..." usemap="#edit<?php echo $recID?>">
      <map name="edit<?php echo $recID?>">
      <area shape=rect coords="0,0,16,16" title='Edit ...' href="./mn.php?mn=e&a=<?php echo $table?>&b=<?php echo $recID?>">
      </map>
      <?php
    }
  }
  $fSubmit = true;
  foreach( $arrNichtLoeschen as $k )
    if( 0 == strcmp( $k, $table ) )
      $fSubmit = false;
  /***
   *** condition for displaying update- and delete-icons
   ***/
  if( $fSubmit && !isset($gutschriftZugestellt) && !$fPopup && !$fKeinDelete && !isset($_E['garbage']) )
  {
    if(0)
    {
      ?><input type=image src='icons/del.gif' name='delete'><?php
    }
    else if( isset( $recID) )
    {
      ?><img src="icons/iconmonstr-trash-can-thin-16.png" alt="Remove ..." usemap="#delete<?php echo $recID?>">
      <map name="delete<?php echo $recID?>">
      <area shape=rect coords="0,0,16,16" title='Remove ...' href="./mn.php?mn=cd&a=<?php echo $table?>&b=<?php echo $recID?>">
      </map>
      <?php
    }
  }
  echo "\n"; // HTML-Quelltext besser lesbar
  ?></td></form><?php
  echo "\n"; // HTML-Quelltext besser lesbar

}
function ausgebenAlsTabelleHorizontal( $spaltenName, $auchID, &$cSpalten, $sql, $zielTabelle, $result, $table, $ID, $ActionSuffix, $arrStyle )
{
global $unterdrueckteSpalte;
global $gruppe;
global $_E;
global $Summenwert;
global $ID1;
global $proj;
global $pw;

  if( isset($_E['ident']) )
    $gruppenStaerke = $_E['ident'];
  else
    $gruppenStaerke = 1;
  $istKeineID = false;
  $i=0;
  foreach( $row as $elem )
  {
    if( $istKeineID )
    {
      if( $i <= $gruppenStaerke )
      {
        if( isset($vgl) )
    $vgl .= $elem;
        else
    $vgl = $elem;
      }
    }
    else
      $istKeineID = true;
    $i++;
  }
  $istKeineID = false;
  $i=0;
  for( $z=0; $z<count($spaltenName); $z++ )  // wegen Datumsformatierung
    $arrFeldTyp[$z] = mysql_field_type( $result, $z );
  for( $z=0; $z<count($spaltenName); $z++ )  // wegen enum-Sofortaenderung
    $arrFeldFlag[$z] = mysql_field_flags( $result, $z );
  for( $z=0; $z<count($spaltenName); $z++ )  // wegen enum-Sofortaenderung
    $arrFeldName[$z] = mysql_field_name( $result, $z );
  while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
  {
    tabellenZeileBeginnen();
    foreach( $row as $elem )
    {
      if( $istKeineID )
      {
        if( false == istForeignKeyName( $spalte[$i] ) )
        {
          $fUnterdruecken=false;
          for($c=0;$c<count($unterdrueckteSpalte);$c++)
            if( $unterdrueckteSpalte[$c] == $spalte[$i] )
              $fUnterdruecken=true;
          if( false == $fUnterdruecken )
          {
            if( isset($arrFeldTyp[$i]) and 'date' == $arrFeldTyp[$i] )
            {
              $arr = explode( "-", $elem );
              if( 4 == strlen( $arr[0] ) )
                $elem = "$arr[2].$arr[1].$arr[0]";
            }
            if( strstr( $spalte[$i], "Euro" ) )
            {
              $align="align=right";
              $Summenwert += $elem;
              $elem = number_format($elem,'2',',','.');
            }
            //include("anzeigeRoutinen.prj");
            echo_("\n\t\t<td bgcolor='#E8E8E8' ");
            $j=$i-1;
            if( isset( $aColspan[$j] ) )//{echo"> $j : $aColspan[$j]</tr></table>";exit;}
              echo_(" colspan=$aColspan[$j]");
            if( !isset($align) )
              $align="";
            echo_("$align><font size='-2'>");
            if( !isset($vgl) )
              $vgl="";
            if( $gruppe <> $vgl || $i > $gruppenStaerke )
              echo_("$elem</font></td>");
          }
        }
      }
      else
      {
        $istKeineID = true;
        if( $fSubmit )
        {
          $str = "./mn.php?mn=3653&a=$table&$proj";
          if( $ActionSuffix )
            $str .= $ActionSuffix;
          formularBeginnen($str, "");
          hiddenFeldSchreiben( "ID", $elem );
          if( $ID1 )
            hiddenFeldSchreiben( "ID1", $ID1 );
          if( isset($_REQUEST['d']) )
            hiddenFeldSchreiben( "d", 1 );
        }
      }
      if( 0 == $i )
        $recID=$elem;
      $i++;
    }
    if( $fSubmit )
    {
      echo_("\n<td>");
      //formularKnopf("l&ouml;schen...", "delete");
      echo_("\n<INPUT TYPE=image src='icons/del.gif' NAME='delete'>");
      echo_("</td>");
      echo_("\n</FORM>");
    }
    if( !isset($vgl) )
      $vgl="";
    if( $gruppe <> $vgl )
      $gruppe = $vgl;
    tabellenZeileBeenden();
  }
}
function ausgebenAlsTabelleVertikal( $spaltenName, $auchID, &$cSpalten, $sql, $zielTabelle, $result, $table, $ID, $ActionSuffix, $arrStyle )
{
  global $enumListe;
  global $_E;
  global $ID1;
  global $proj;
  global $pw;

  if( isset($_E['ident']) )
    $gruppenStaerke = $_E['ident'];
  else
    $gruppenStaerke = 1;
  $cSpalten = 0;
  $anz = count( $spaltenName );
  echo_("\n\t<tr bgcolor=#D0D0D0>");
  if( $auchID )
  {
    echo_("\n\t<th><font size='-2'>");
    //echo $spaltenName[0];// is ja immer die 1. Spalte
    echo_("\n\t</th>");
  }

  // Die Datenausgabe einstellen ...
  $enumIDX=1;
  $strKey=$table;
  if( !isset($enumListe["$strKey"]) )
  {
    $strKey .= "_$enumIDX";
    $enumIDX++;
  }
  if( isset($enumListe["$strKey"]) )
  {
    $enumListe["$strKey"]=str_replace( "&uuml;", "ü", $enumListe["$strKey"] );
    $enumListe["$strKey"]=str_replace( "&ouml;", "ö", $enumListe["$strKey"] );
    $enumListe["$strKey"]=str_replace( "&auml;", "ä", $enumListe["$strKey"] );
  }
  //  $str = "./mn.php?mn=7774&a=$table&$proj";
  $str = $ActionSuffix;
  formularBeginnen($str, "NAME='frm$table' onSubmit='return pruefenEingaben(this)'");
  $arr = mysql_fetch_row( $result );
  $anz = mysql_num_fields($result);
  for( $i=1; $i < $anz; $i++ )
  {
    if( false == istForeignKeyName( $spaltenName[$i] ) )
    {
      echo_("\n\t<th align=left width=1><font size='-2'>");
/*** Ausgabe der Spaltennamen                                              ***/
      echo_($spaltenName[ $i ]);
/*** Ausgabe mit Aenderungsmoeglichkeit                                    ***/
//    echo_("$table, $i : " . $spaltenName[ $i ]);
      echo_("\n\t</th>");
      if( isset($enumListe["$strKey"]) )
        ausgebenInZelle( $table, $result, $i, $arr[$i], $enumListe["$strKey"], 0, $fEnum, $arrStyle[$i] );
      else
        ausgebenInZelle( $table, $result, $i, $arr[$i], "", 0, $fEnum, $arrStyle[$i] );
      if( $fEnum )
      {
        if( !isset($enumListe[$table]) )
        {
          $strKey=$table;
          $strKey .= "_$enumIDX";
          $enumIDX++;
        }
        if( isset($enumListe[$strKey]) )
          $enumListe[$strKey]=str_replace( "&uuml;", "ü", $enumListe[$strKey] );
      }
      echo_("\n\t</tr>");
      echo_("\n\t<tr bgcolor=#D0D0D0>");
      $cSpalten++;
    }
  }
  hiddenFeldSchreiben( "ID", $ID );
  if( $ID1 )
    hiddenFeldSchreiben( "ID1", $ID1 );
  if( isset($_REQUEST['d']) )
    hiddenFeldSchreiben( "d", 1 );
  echo "<td colspan=2 align=center>";
  formularKnopf("&auml;ndern", "");
  echo "</td>";
  echo"\n</FORM>";

  if( !$zielTabelle )  // Hier soll keine Druckansicht angeboten werden, z.B. in der Preisansicht
    echo_("\n\t</tr>");
  else if( "ohne submit Knopf" <> $zielTabelle )
  {
    $str=str_replace( " ", "%20", $sql );
    $str=str_replace( "&uuml;", "%FC", $str );
    $Bezug="";
    echo_("\n\t<th><font size='-2'>");
//    echo_("\n<A HREF=\"./eiZu.php?wZu=zeigendDruckansicht&zielTabelle=$zielTabelle&sql=$str&Bezug=$Bezug&bgcolor=white&gruppenStaerke=$gruppenStaerke&$proj\">Druckansicht</A>");
    echo_("\n</th>");
    echo_("\n</tr>");
  }
}
function ausgebenAlsTabelleZumVertikalenAendern( $spaltenName, $auchID, &$cSpalten, $sql, $zielTabelle, $result, $table, $ID, $ActionSuffix="" )
{
  global $enumListe;
  global $_E;
  global $ID1;
  global  $proj;
  global  $pw;

  if( isset($_E['ident']) )
    $gruppenStaerke = $_E['ident'];
  else
    $gruppenStaerke = 1;
  $cSpalten = 0;
  $anz = count( $spaltenName );
  echo_("\n\t<tr>");
  if( $auchID )
  {
    echo_("\n\t<th>");
    //echo $spaltenName[0];// is ja immer die 1. Spalte
    echo_("\n\t</th>");
  }

  // Die Datenausgabe einstellen ...
  $enumIDX=1;
  $strKey=$table;
  if( !isset($enumListe["$strKey"]) )
  {
      $strKey .= "_$enumIDX";
      $enumIDX++;
  }
  if( isset($enumListe["$strKey"]) )
  {
    $enumListe["$strKey"]=str_replace( "&uuml;", "ü", $enumListe["$strKey"] );
    $enumListe["$strKey"]=str_replace( "&ouml;", "ö", $enumListe["$strKey"] );
    $enumListe["$strKey"]=str_replace( "&auml;", "ä", $enumListe["$strKey"] );
  }
  $str = "./mn.php?mn=7774&a=$table";
  // ActionSuffix nicht, 
  //$str .= $ActionSuffix;
//echo "proj : $proj ; ActionSuffix : $ActionSuffix <p>"; exit;
  if( isset($_E['mainLink']) )
  {
    /***
     *** da erst nach Speichern minorLink uebergeben wird,
     *** darf die vom Editier-Ziel abweichende
     *** ID und Entitaet hier noch nicht unmittelbar gesetzt werden.
     ***
     ***/
     //$str_ = str_replace("&a", "&a_", $_E['mainLink']);
     //$str .= "&d=&minorLink=$str_";
  }
  formularBeginnen($str, "name='frm$table' onSubmit='return pruefenEingaben(this)'");
  $arr = mysql_fetch_row( $result );
  $anz = mysql_num_fields($result);

  for( $i=1; $i < $anz; $i++ )
  {
    if( false == istForeignKeyName( $spaltenName[$i] ) )
    {
      echo_("\n\t<th>");
      echo_($spaltenName[ $i ]);
      echo_("\n\t</th>");

      if( isset($enumListe["$strKey"]) )
        formularAttribut( $table, $result, $i, $arr[$i], $enumListe["$strKey"], 80, $fEnum, $strKey );
      else
        formularAttribut( $table, $result, $i, $arr[$i], "", 80, $fEnum );//fEnum = true, wenn es ein enum-Feld war
      if( $fEnum )
      { // enum-Wert wurde ausgegeben
        if( !isset($enumListe[$table]) )
        {
          $strKey=$table;
          $strKey .= "_$enumIDX";
          $enumIDX++;
        }
        if( isset($enumListe[$strKey]) )
          $enumListe[$strKey]=str_replace( "&uuml;", "ü", $enumListe[$strKey] );
        $fEnum = false;
      }
      echo_("\n\t</tr>");
      echo_("\n\t<tr>");
      $cSpalten++;
    }
  }
  hiddenFeldSchreiben( "ID", $ID );
  if( $ID1 )
    hiddenFeldSchreiben( "ID1", $ID1 );
  if( isset($_REQUEST['d']) )
    hiddenFeldSchreiben( "d", 1 );
  /***
   *** fortsetzen-Link ueberschreiben
   ***/
  if( isset($_E['mainLink']) )
    hiddenFeldSchreiben( "__#__mainLink", $_E['mainLink'] );
  echo "<td colspan=2 align=center>";
  formularKnopf("&Auml;nderung &uuml;bernehmen", "");
  echo "</td>";
  echo"\n</FORM>";

  if( !$zielTabelle )  // Hier soll keine Druckansicht angeboten werden, z.B. in der Preisansicht
      echo_("\n\t</tr>");
  else if( "ohne submit Knopf" <> $zielTabelle )
  {
    $str=str_replace( " ", "%20", $sql );
    $str=str_replace( "&uuml;", "%FC", $str );
        $Bezug="";
    echo_("\n\t<th>");
//    echo_("\n<A HREF=\"./eiZu.php?wZu=zeigendDruckansicht&zielTabelle=$zielTabelle&sql=$str&Bezug=$Bezug&bgcolor=white&gruppenStaerke=$gruppenStaerke&$proj\">Druckansicht</A>");
    echo_("\n</th>");
    echo_("\n</tr>");
  }
}
function ausgebenAlsAenderbareTabellenzeile( $result ,$table, $ID, $enumListe, $ActionSuffix )
{
  global $ID1;
  global  $proj;
  global  $pw;
  $enumListe=str_replace( "&uuml;", "ü", $enumListe );
  $str = "./mn.php?mn=7774&a=$table&$proj";
  $str .= $ActionSuffix;
  formularBeginnen($str, "NAME='frm$table' onSubmit='return pruefenEingaben(this)'");
  $arr = mysql_fetch_row( $result );
  $anz = mysql_num_fields($result);
  for( $i=1; $i < $anz; $i++ )
  {
     if( false == istForeignKeyName( mysql_field_name( $result, $i ) ) )
      formularAttribut( $table, $result, $i, $arr[$i], $enumListe, 0, $fEnum );
  }
  hiddenFeldSchreiben( "ID", $ID );
  if( $ID1 )
    hiddenFeldSchreiben( "ID1", $ID1 );
  if( isset($_REQUEST['d']) )
    hiddenFeldSchreiben( "d", 1 );
  echo "<td>";
  formularKnopf("&Auml;nderung &uuml;bernehmen", "");
  echo "</td>";
  echo"\n</FORM>";
}
/***************************************
 * Parameter:
 * $label  Ein Buchstabe, welcher die Tabelle und den Select indiziert
 * $table  Tabellenname im Hidden-Feld
 *
 * In der SELECT-Liste ist der VALUE das ID-Feld,
 * der Text ist der zur ID gehörende Text
 ***************************************************************************/
function ListeMitID( $result, $label, $table, $fDatum, $anzuzeigen )
{
  global $keinInsert;
  global $SELECTRE1;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTRE2;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTRE3;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTRE4;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTRE5;  // im Falle von 'zurueck zum Neuanlegen'
  $tiefe=0;
  if( "RE1" == $label && isset($SELECTRE1) )
  {
    $IDgewaehlt=$SELECTRE1;
    echo"\n<!-- SELECTRE1 = $SELECTRE1 -->";
  }
  else if( "RE2" == $label )
  {
    $IDgewaehlt=$SELECTRE2;
    echo"\n<!-- SELECTRE2 = $SELECTRE2 -->";
  }
  else if( "RE3" == $label )
  {
    $IDgewaehlt=$SELECTRE3;
    echo"\n<!-- SELECTRE3 = $SELECTRE3 -->";
  }
  else if( "RE4" == $label )
  {
    $IDgewaehlt=$SELECTRE4;
    echo"\n<!-- SELECTRE4 = $SELECTRE4 -->";
  }
  else if( "RE5" == $label )
  {
    $IDgewaehlt=$SELECTRE5;
    echo"\n<!-- SELECTRE5 = $SELECTRE5 -->";
  }
  $anz = mysql_num_fields($result);
  if( !isset($keinInsert) or false == $keinInsert )
  {
    echo "\n";
    ?><input type='hidden' name='Tabelle<?php
    echo $label;
    ?>' value='<?php
    echo $table;
    ?>'><?php echo "\n";
    ?><select name='SELECT<?php
    echo $label;
    ?>' id='SELECT<?php
    echo "$label";
    ?>'><?php
  }
  $f=false;

  while( $row=mysql_fetch_array( $result, MYSQL_ASSOC ) )
  {
    $id = true;   // Option Value ist die ID
    foreach( $row as $elem )
    {
      echo "\n";
      if( $id )
      {
        if( !isset($keinInsert) or false == $keinInsert )
        {
          ?><option value='<?php
          echo "$elem";
          ?>'<?php
        }
        if( isset($IDgewaehlt) and $IDgewaehlt )
        {
          if( $elem==$IDgewaehlt )
          {
            if( !isset($keinInsert) or false == $keinInsert )
            {
              ?> selected<?php
            }
          }
        }
        else if( !$f )
        {
          if( !isset($keinInsert) or false == $keinInsert )
          {
            ?> selected<?php
          }
          $f = true;
        }
        if( !isset($keinInsert) or false == $keinInsert )
        {
          ?>><?php
        }
        $id = false;
      }
      else if( !$id )
      {
        if( $fDatum )
        {
          $arr = explode( "-", $elem );
          if( 4 == strlen( $arr[0] ) )
            $elem = "$arr[2].$arr[1].$arr[0]";
        }
        if( !isset($keinInsert) or false == $keinInsert )
          echo "$elem";
        ++$tiefe;
        if( $tiefe == $anzuzeigen )
        {
          $id = true;
          $tiefe=0;
          break;// nur soviele Felder nach der ID ausgeben
        }
        else
        {
          ?> <?php
        }
      }
    }
  }
  if( !isset($keinInsert) or false == $keinInsert )
  {
    ?></select><?php
  }
}
function ergebnisListeMitID( $label, $table, $anz, $id, $zeilen )
{
  global $SELECTEM1;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTMM1;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTSL1;  // im Falle von 'zurueck zum Neuanlegen'
  global $SELECTSL2;  
  global $SELECTSL3;  
  global $SELECTSL4;  
  global $SELECT0;  // im Falle von 'EMspazierend'
  global $exclusiv0;  // im Falle von 'EMspazierend'
  global $keinInsert;

  /*** wenn als erstes mit "EM1" verglichen wird, trifft der Vergleich**
   *** zu im Falle von $label='0', wenn Aufruf aus "auflistend"      ***/
  if( '0' == $label )
  {
    $IDgewaehlt=$SELECT0;
  }
  else if( "EM1" == $label )
  {
    $IDgewaehlt=$SELECTEM1;
  }
  else if( "MM1" == $label )
  {
    $IDgewaehlt=$SELECTMM1;
  }
  else if( "SL1" == $label and isset($_REQUEST["SELECTSL1"]) )
  {
    $IDgewaehlt=$_REQUEST["SELECTSL1"];
    //echo "IDgewaehlt : $IDgewaehlt <br>";
    //$IDgewaehlt=$SELECTSL1;
  }
  else if( "SL1" == $label and isset($_REQUEST["sl1ID"]) )
  {
    $IDgewaehlt=$_REQUEST["sl1ID"];
  }
  else if( "SL2" == $label and isset($_REQUEST["sl2ID"]) )
  {
    $IDgewaehlt=$_REQUEST["sl2ID"];
  }
  else if( "SL2" == $label and isset($_REQUEST["SELECTSL2"]) )
  {
    $IDgewaehlt=$_REQUEST["SELECTSL2"];
  }
  else if( "SL3" == $label )
  {
    $IDgewaehlt=$SELECTSL3;
  }
  else if( "SL4" == $label )
  {
    $IDgewaehlt=$SELECTSL4;
  }
  //$reihen=count($zeilen) / $anz;
  //$size=min($reihen,15);
  //$size=max($size,1);
  if( !isset($keinInsert) or false == $keinInsert )
  {
    ?><input type='hidden' name='Tabelle<?php
    echo $label;
    ?>' value='<?php
    echo $table;
    ?>'><?php echo "\n";
    ?><select name='SELECT<?php
    echo "$label";
    ?>' id='SELECT<?php
    echo "$label";
    ?>'><?php
  }
  $i=0;
  $record=0;
  $fSelected = false;
  while( $i<count($zeilen) )
  {
    echo "\n";
    if( $exclusiv0 )
    {
      if( $id[$record]==$IDgewaehlt )
      {
        if( !isset($keinInsert) or false == $keinInsert )
        {
          ?><option value='<?php
          echo "$id[$record]";
          ?>' SELECTED><?php
        }
        for( $j=0; $j < $anz; $j++, $i++ )
          if( !isset($keinInsert) or false == $keinInsert )
            echo "$zeilen[$i] ";
        break;
      }
      else
      {
        $record++;
        for( $j=0; $j < $anz; $j++, $i++ )
          ;//naechsten Inhalt einstelln
        continue;
      }
    }
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?><option value='<?php
      echo "$id[$record]";
      ?>'<?php
    }
    if( isset($IDgewaehlt) and $IDgewaehlt )
    {
      if( $id[$record]==$IDgewaehlt )
      {
        if( !isset($keinInsert) or false == $keinInsert )
        {
          ?> SELECTED<?php
        }
      }
    }
    else if( !$fSelected )
    {
      if( !isset($keinInsert) or false == $keinInsert )
      {
        ?> SELECTED<?php
      }
      $fSelected = true;
    }
    if( !isset($keinInsert) or false == $keinInsert )
    {
      ?>><?php
    }
    $record++;
    for( $j=0; $j < $anz; $j++, $i++ )
      if( !isset($keinInsert) or false == $keinInsert )
        echo "$zeilen[$i] ";
  }
  if( !isset($keinInsert) or false == $keinInsert )
  { 
    ?></select><?php
  }
}
function ergebnisBoxenMitID( $label, $table, $anz, $id, $exclude, $zeilen, $zielTabelle, $anzBoxen )
{
  ?><input type='hidden' name='Tabelle<?php
  echo "$label";
  ?>' value='<?php
  echo "$table";
  ?>'><?php
  $i=0;
  $record=0;
  $anzBoxen = 0;
  $letzte=$anz-1;
  while( $i<count($zeilen) )
  {
    if( 99 < $record )
      break;// mehr nicht
    if( !$id[$record] )
      break;
    if( $id[$record] == $exclude[$record] )
    {
      $record++;
      for( $j=0; $j < $anz; $j++ )
        $i++;
      continue;
    }
    $anzBoxen++;
    ?><input type checkbox name='CHECKBOX<?php
    echo "$label";
    $idx = $letzte+$i;
    if( strstr( $zeilen[$idx], "flaechengestuft" ) )
      $flag='f';
    else if( strstr( $zeilen[$idx], "lfm" ) )
      $flag='l';
    else if( strstr( $zeilen[$idx], "qm" ) )
      $flag='q';
    else if( strstr( $zeilen[$idx], "Stück" ) )
      $flag='s';
    else
      $flag='?';

    ?>_<?php
    if( 10 > $record )
    {
      ?>0<?php
    }
    echo "$record' value='$id[$record]' onClick=\"triggerCheckbox(this,$record,'$flag','$zielTabelle')\">";
//    echo "_$record' value='$id[$record]' onClick=\"triggerCheckbox(this,$record,'$zeilen[$idx]')\">";
    $record++;
    for( $j=0; $j < $anz; $j++, $i++ )
      echo "$zeilen[$i] ";
    echo"&nbsp;(Pos. $record)";
    ?><p><?php
  }
}
function ausgebenAlsNeueTabellenzeile( $result, $table, $enumListe = "" )
{
  global $enumListe;
  global $_E;
  /***
   *** geht bisher nur mit enumListe-Schluessel[$table]
   *** es gibt allerdings auch enumListe-Schluessel[$table . "_1"] und hoeher
   ***
   ***/
  if( isset($enumListe[$table . "_1"]) )
  {
    $c=1;
    $eL = $enumListe[$table . "_" . $c];
  }
  else
    //$eL = $enumListe;
    $eL = $enumListe[$table];
  $anz = mysql_num_fields($result);
  /***
   *** get name of first input-field
   *** will be focused in beendenTabelle.inc
   ***/
  $_E['focusMe'] = "frm" . $table . "." . $table . "_" . mysql_field_type( $result, 1 ) . "_" . mysql_field_name( $result, 1 ) . ".focus()";
  for( $i=1; $i < $anz; $i++ )
  {//var_dump($eL);
    formularAttribut( $table, $result, $i, "", $eL, 0, $fEnum );
    if( isset($c) and true == $fEnum )
    {
      ++$c;
      unset($eL);
      $eL = $enumListe[$table . "_" . $c];
    }
  }
}
/*************************************
 ********************************************/
function anzeigenTabelle( $tabKopf, $zeilen, $align )
{
  global $gfTabelleUntenOffen;// wenn gesetzt, gibts kein </table> TAG
  global $gfTabelleObenOffen;
  global $gTableAlign;

  if( !$gfTabelleObenOffen )
  {
    ?><table><?php
  }
  ?><tr><?php
  $anz = count($tabKopf);
  for( $i=0; $i < $anz; $i++ )
  {
    ?><th><?php
    echo $tabKopf[ $i ];
    ?></th><?php
  }
  ?></tr><?php

  for( $i=0; $i < count($zeilen); )
  {
    ?><tr><?php
    for( $j=0; $j < $anz; $j++ )
    {
      ?><td><?php
      echo $zeilen[ $i++ ];
      ?></td><?php
    }
    ?></tr><?php
  }
  if( !$gfTabelleUntenOffen )
  {
    ?></table><?php
  }
}
function anzeigenTabelleMitLink( $tabKopf, $zeilen, $align, $arrID, $arrNLID, $cFeld, $wZu, $dimStatCol, $tmpBGNLSummen )
{
  global $gfTabelleUntenOffen;// wenn gesetzt, gibts kein </table> TAG
  global $gfTabelleObenOffen;
  global $MySQLDb;

  if( !$gfTabelleObenOffen )
    echo_("\n<table width=90% border=0 cellpadding='2' cellspacing='2'>");
  echo_("\n<tr bgcolor=#D0D0D0>");
  $anz = count($tabKopf);
  echo_("\n\t<th></th>");
  for( $i=0; $i < $anz; $i++ )
  {
    echo_("\n\t<th><font size='-2'>");
    echo_($tabKopf[ $i ]);
    echo_("</th>");
  }
  echo_("\n</tr>");

  $cArr=0;
  $zeile=1;
  $currentNLID=$arrNLID[0];/*** 1. Niederlassung einstellen ***/
  for( $i=0; $i < count($zeilen); )
  {
    if( $currentNLID != $arrNLID[$cArr] )  /*** Niederlassungswechsel ***/
    {
      $sql="SELECT SUM(Sollkosten), SUM(NU_KostenSoll), SUM(NU_KostenLstg), SUM(RisikoSoll), SUM(RisikoLstg), SUM(Leistung) FROM " . $tmpBGNLSummen . " WHERE NiederlassungID=$currentNLID";
      $arr_[0]=0;   // SUM(Sollkosten)
      $arr_[1]=1;   // SUM(NU_KostenSoll)
      $arr_[2]=2;   // SUM(NU_KostenLstg)
      $arr_[3]=3;   // SUM(RisikoSoll)
      $arr_[4]=4;   // SUM(RisikoLstg)
      $arr_[5]=5;   // SUM(Leistung)
      gibFelderArray( $MySQLDb, $sql, $arr_ );
      if( false == habWas( $arr_, 0, 5 ) )
      {
        echo"\n<h3>interner Fehler: Tabelle '$tmpBGNLSummen' konnte nicht ausgelesen werden</h3>";
        exit;
      }
      $prozent_= $deckung_=$arr_[0]-$arr_[1]-$arr_[3];
      $prozent = $deckung =$arr_[5]-$arr_[2]-$arr_[4];
      $ist=$arr_[1]+$arr_[2];
      $risiko=$arr_[3]+$arr_[4];

      // Deckung in Prozent:
      $einProzent = $arr_[0] / 100;
      if( $einProzent )
        $prozent_ /= $einProzent;
      else
        $prozent_ = 0;
      $einProzent = $arr_[5] / 100;
      if( $einProzent )
        $prozent /= $einProzent;
      else
        $prozent = 0;

      $formDec_=number_format($deckung_,'2',',','.');
      $formPro_=number_format($prozent_,'2',',','.');
      $formPro_ .= "%";
      $formDeck=number_format($deckung ,'2',',','.');
      $formProz=number_format($prozent ,'2',',','.');
      $formProz .= "%";
      $formSoll=number_format($arr_[0],'2',',','.');
      $formIst =number_format($ist,'2',',','.');
      $formLstg=number_format($arr_[5],'2',',','.');
      $formRis =number_format($risiko,'2',',','.');
      $i_=$i - $anz;// das ist der Name der letzten NL, die gerade fertig wurde
      echo"\n<tr><td colspan=15 align=right><A HREF=\"#0\">-&nbsp;zur NL-Auswahl&nbsp;-&nbsp;&nbsp;</A><A NAME=\"$currentNLID\">Ergebnis $zeilen[$i_]:</A></td><td align='right'><br>$formIst<hr></td><td align='right'><br>$formRis<hr></td><td align='right'><br>$formSoll<hr></td><td align='right'><br>$formDec_<hr></td><td align='right'><br>$formPro_<hr></td><td></td><td align='right'><br>$formLstg<hr></td><td align='right'><br>$formDeck<hr></td><td align='right'><br>$formProz<hr></td></tr>";
      $currentNLID = $arrNLID[$cArr];
    }
    $anfang = $zeile % 10;
    if( !$anfang )
    {
      echo"<tr bgcolor=#D0D0D0>";
      echo_("\n\t<th></th>");
      for( $h=0; $h < $anz; $h++ )
      {
        echo_("\n\t<th><font size='-2'>");
        echo_($tabKopf[ $h ]);
        echo_("</th>");
      }
      echo_("\n</tr>");
    }
    echo_("\n<tr>");
    echo_("\n\t<td bgcolor='#E8E8E8' align='$align'>");
    echo_("$zeile</td>");
    ++$zeile;
    $dynCol=0;
    for( $j=0; $j < $anz; $j++ )
    {
      if( $dimStatCol <= $j )
      {
        if( 0 == $dynCol % 3 )
        {
          if( true == $fToggleDynCol )
            $fToggleDynCol=false;
          else
            $fToggleDynCol=true;
        }
        ++$dynCol;
        if( false == $fToggleDynCol )
          $bgcolor="#E8E8E8";
        else
          $bgcolor="burlywood";
      }
      else
      {
        $fToggleDynCol=false;
        $bgcolor="white";
      }
      echo_("\n\t<td bgcolor='$bgcolor' align='$align'>");
      if( $j == $cFeld )
      {
        echo_("\n<A HREF=\"javascript:zurVergabe('./index.autorisiert.php?auswahl=vergabe&setzenID=$arrID[$cArr]')\">");
        $cArr++;
      }
      echo_($zeilen[ $i++ ]);
      if( $j == $cFeld )
        echo_("</A>");
      echo_("</td>");
    }
    echo_("\n</tr>");
  }
  $sql="SELECT SUM(Sollkosten), SUM(NU_KostenSoll), SUM(NU_KostenLstg), SUM(RisikoSoll), SUM(RisikoLstg), SUM(Leistung) FROM " . $tmpBGNLSummen . " WHERE NiederlassungID=$currentNLID";
  $arr_[0]=0;   // SUM(Sollkosten)
  $arr_[1]=1;   // SUM(NU_KostenSoll)
  $arr_[2]=2;   // SUM(NU_KostenLstg)
  $arr_[3]=3;   // SUM(RisikoSoll)
  $arr_[4]=4;   // SUM(RisikoLstg)
  $arr_[5]=5;   // SUM(Leistung)
  gibFelderArray( $MySQLDb, $sql, $arr_ );
  if( false == habWas( $arr_, 0, 5 ) )
  {
    echo"\n<h3>interner Fehler: Tabelle '$tmpBGNLSummen' konnte nicht ausgelesen werden</h3>";
    exit;
  }
  $prozent_= $deckung_=$arr_[0]-$arr_[1]-$arr_[3];
  $prozent = $deckung =$arr_[5]-$arr_[2]-$arr_[4];
  $ist=$arr_[1]+$arr_[2];
  $risiko=$arr_[3]+$arr_[4];

  // Deckung in Prozent:
  $einProzent = $arr_[0] / 100;
  if( $einProzent )
    $prozent_ /= $einProzent;
  else
    $prozent_ = 0;
  $einProzent = $arr_[5] / 100;
  if( $einProzent )
    $prozent /= $einProzent;
  else
    $prozent = 0;

  $formDec_=number_format($deckung_,'2',',','.');
  $formPro_=number_format($prozent_,'2',',','.');
  $formPro_ .= "%";
  $formDeck=number_format($deckung ,'2',',','.');
  $formProz=number_format($prozent ,'2',',','.');
  $formProz .= "%";
  $formSoll=number_format($arr_[0],'2',',','.');
  $formIst =number_format($ist,'2',',','.');
  $formLstg=number_format($arr_[5],'2',',','.');
  $formRis =number_format($risiko,'2',',','.');
  $i_=$i - $anz;// das ist der Name der letzten NL, die gerade fertig wurde
  echo"\n<tr><td colspan=15 align=right><A HREF=\"#0\">-&nbsp;zur NL-Auswahl&nbsp;-&nbsp;&nbsp;</A><A NAME=\"$currentNLID\">Ergebnis $zeilen[$i_]:</A></td><td align='right'><br>$formIst<hr></td><td align='right'><br>$formRis<hr></td><td align='right'><br>$formSoll<hr></td><td align='right'><br>$formDec_<hr></td><td align='right'><br>$formPro_<hr></td><td></td><td align='right'><br>$formLstg<hr></td><td align='right'><br>$formDeck<hr></td><td align='right'><br>$formProz<hr></td></tr>";
  echo_("\n");
  if( !$gfTabelleUntenOffen )
    echo_("</table>\n");
}
function ausgebenInZelle( $table, $result, $i, $attr, $enumListe, $laengeBeiText, &$fEnum, $style )
{
  $feldName = mysql_field_name( $result, $i );
  $feldTyp = mysql_field_type( $result, $i );
  $feldFlag = mysql_field_flags( $result, $i );

  if( isset($debug) )
  {
    for( $j=0; $j < count($feldFlag); $j++ )
      echo "\nfeldFlag : $feldFlag<br>";
    for( $j=0; $j < count($feldTyp); $j++ )
      echo "\nfeldTyp : $feldTyp<br>";
  }
  echo "\n\t<td style='font-weight:$style' bgcolor='#E8E8E8'><font size='-2'>";
  if( strstr( $feldFlag, "enum" ) )
    $fEnum = true;
  else
    $fEnum = false;
  if( strstr( $feldFlag, "enum" ) )
  {
    $arr = explode(",", $enumListe);
    $idx=0;
    for( $j=0; $j<count($arr); $j++ )
    {
      if( $attr==$arr[$j] )
        $idx=$j;
      // echo"\nattr==arr[$j] : $attr==$arr[$j]\n";
    }
    for( $j=0; $j<count($arr); $j++ )
    {
      if( $idx==$j )
        echo $arr[$j];
    }
  }
  else if( "date" == $feldTyp )
  {
    if( false/*!$attr*/ )
    {/*** keine Vorbelegung mehr mit Tagesdatum, weil inzwischen**
      *** viele Attribute, wegen denen auch die Aenderung aufge-**
      *** rufen werden kann                                     ***/
      $datum = date("d.m.Y",time());
      echo" class=rechnungZeichenWichtig"; 
    }
    else if( "0000-00-00" == $attr )
      $datum="";
    else
    {
      $arr = explode( "-", $attr );
      if( 4 == strlen( $arr[0] ) )
        $datum = "$arr[2].$arr[1].$arr[0]";
      else
        $datum = $attr;
    }
    echo " $datum";
  }
  else if( "time" == $feldTyp )
  {
    if( $attr )
    {
      $arr = explode( ":", $attr );
      $time = "$arr[0]:$arr[1]";
    }
    else
      $time="01:00";
    echo " $time";
  }
  else
  {
    echo " $attr";
    if( $laengeBeiText )
      echo " SIZE=$laengeBeiText";
  }
  echo "</font></td>";
}
function formularAttribut( $table, $result, $i, $attr, $enumListe, $laengeBeiText, &$fEnum, $clutch="" )
{
  global $enumOVL;
  $feldName = mysql_field_name( $result, $i );
  $feldTyp = mysql_field_type( $result, $i );
  $feldFlag = mysql_field_flags( $result, $i );

  if( isset($debug) )
  {
    for( $j=0; $j < count($feldFlag); $j++ )
      echo "\nfeldFlag : $feldFlag<br>";
    for( $j=0; $j < count($feldTyp); $j++ )
      echo "\nfeldTyp : $feldTyp<br>";
    echo "\nattr : $attr<br>";
  }
  echo "\n\t<td>\n\t\t<";
  if( strstr( $feldFlag, "enum" ) )
  {
    echo "SELECT ";
    $fEnum = true;
  }
  else if( strstr( $feldFlag, "blob" ) )
    echo "TEXTAREA ";
  else
  {
    echo "INPUT ";
    $fEnum = false;
  }
  echo "NAME='$table" . "_" . $feldTyp . "_" . "$feldName'";
  if( strstr( $feldFlag, "enum" ) )
  {
    echo " SIZE='1'>";
    $arr = explode(",", $enumListe);
    for($e=0;$e<count($arr);$e++)
      echo "\n" . $arr[$e] . "<br>";
    if( isset($enumOVL[$clutch]) )
      $aOVL = explode(",", $enumOVL[$clutch]);
    $idx=0;
    for( $j=0; $j<count($arr); $j++ )
    {
      if( $attr==$arr[$j] )
        $idx=$j;
      // echo"\nattr==arr[$j] : $attr==$arr[$j]\n";
    }
    for( $j=0; $j<count($arr); $j++ )
    {
      echo "\n\t\t<OPTION VALUE='$arr[$j]'";
      if( $idx==$j )
        echo " SELECTED>";
      else
        echo ">";
      
    if( isset($aOVL) )
      echo $aOVL[$j];
    else
      echo $arr[$j];
    }
    echo "\n\t\t</select";
  }
  else if( "date" == $feldTyp )
  {
    $datum = setFieldDate($attr, $fHTML5);
    include("vorbelegenDatumRE.prj");
    if( false/*!$attr*/ )
    {/*** keine Vorbelegung mehr mit Tagesdatum, weil inzwischen**
      *** viele Attribute, wegen denen auch die Aenderung aufge-**
      *** rufen werden kann                                     ***/
      $datum = date("d.m.Y",time());
      echo" class=rechnungZeichenWichtig"; 
    }
    $datum = setFieldDate($attr, $fHTML5);
    echo " TYPE='";
    if( true == $fHTML5 )
      echo "DATE";
    else
      echo "TEXT";
    echo "' VALUE='$datum'";
  }
  else if( "time" == $feldTyp )
  {
    if( $attr )
    {
      $arr = explode( ":", $attr );
      $time = "$arr[0]:$arr[1]";
    }
    else
      $time="01:00";
    echo " TYPE='TEXT' VALUE='$time'";
  }
  else if( strstr( $feldFlag, "blob" ) )
  {
    echo " COLS=86 ROWS=3 WRAP=PHYSICAL>$attr</TEXTAREA";
  }
  else
  {
    echo " TYPE='TEXT' VALUE='$attr'";
    if( $laengeBeiText )
      echo " SIZE=$laengeBeiText";
  }
  echo "></td>";
}
function lfSeitenquelltext()
{
  echo "\n";
}
?>
