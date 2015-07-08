<?php
if( isset($_E['wZu']) ) // in FBS1-Modulen ist meistens noch $wZu direkt gesetzt
  $wZu = $_E['wZu'];
function logForkedModul( $str )
{
  echo"\n<!-- Modul $str: -->\n";
}
$wZu = $_E['wZu'];
switch( $wZu )
{
  case "dokumentierend":
//    include("ruecksprungURL.js");
    break;
}

include("forkAutomat.inc");

echo"\n\n<!-- Verzweigung, es wird jetzt die Automatentabelle $wZu aus forkAutomat.inc benutzt -->\n\n";

if( file_exists("$wZu.css") )
   include("$wZu.css");

if( ( isset( $_REQUEST["docZustand"] ) and $wZu == $_REQUEST["docZustand"] ) or( false == isset( $_REQUEST["docZustand"] ) and isset($_REQUEST["forkdocC"]) ) )
{ // Ablaufdiagramm erzeugen anstelle der normalen Anzeige
  $docIdx=$_REQUEST["forkdocC"];
  $DOC_ROOT="/var/www/rechnungen/";
  $DOC_WEBALIAS="/rechnungen/";
  $datei=$DOC_ROOT . "fork" . $docIdx . ".tex";
  // Ablaufdiagramm:
  anhaengenAnDatei( $datei, "\\texttt{" );
  anhaengenAnDatei( $datei, "$wZu}:\n" );
  anhaengenAnDatei( $datei, "\paragraph{Ablaufdiagramm $docIdx : $wZu}" );
  anhaengenAnDatei( $datei, "\n\begin{tikzpicture}" );
  anhaengenAnDatei( $datei, "\n[auto," );
  anhaengenAnDatei( $datei, "\n block/.style   ={rectangle, draw=blue, thick, fill=blue!20," );
  anhaengenAnDatei( $datei, "\n text width=15em, text centered, rounded corners," );
  anhaengenAnDatei( $datei, "\n minimum height=4em}," );
  anhaengenAnDatei( $datei, "\n line/.style    ={draw, thick, -latex’,shorten >=2pt}" );
  anhaengenAnDatei( $datei, "\n ]" );
  anhaengenAnDatei( $datei, "\n\matrix [column sep=5mm,row sep=7mm]" );
  anhaengenAnDatei( $datei, "\n{" );
  $seitenVol=12;
  $i=1;
  $f=false;
  $limit=$seitenVol;
  foreach( $forkAutomat[$wZu] as $include )
  {
    anhaengenAnDatei( $datei, "\n% row $i" );
    anhaengenAnDatei( $datei, "\n\\node [block] ($i)     " );
    anhaengenAnDatei( $datei, "{" );
    $include=str_replace( "_", "\\_", $include );
    anhaengenAnDatei( $datei, "$include" );
    anhaengenAnDatei( $datei, "}" );
    anhaengenAnDatei( $datei, "; & \\\\" );
    ++$i;
    if( $limit < $i )
    { // mehr als 12 gehen nicht auf eine Seite
      $f=true;
      $limit=$i-1;
      break;
    }
  }
  $stop=$i-1;
  anhaengenAnDatei( $datei, "\n};" );
  $i=1;
  foreach( $forkAutomat[$wZu] as $include )
  {
    $j = $i + 1;
    if( $stop < $j )
      break;
    anhaengenAnDatei( $datei, "\n\draw [->,black,thick] ($i.south) -- ($j.north) node [right,midway] { };" );
    ++$i;
  }
  if( true == $f )
  { // geht nicht alles auf eine Seite
    anhaengenAnDatei( $datei, "\n\end{tikzpicture}\n" );
    anhaengenAnDatei( $datei, "\paragraph{Ablaufdiagramm $docIdx}" );
    anhaengenAnDatei( $datei, "\n\begin{tikzpicture}" );
    anhaengenAnDatei( $datei, "\n[auto," );
    anhaengenAnDatei( $datei, "\n block/.style   ={rectangle, draw=blue, thick, fill=blue!20," );
    anhaengenAnDatei( $datei, "\n text width=15em, text centered, rounded corners," );
    anhaengenAnDatei( $datei, "\n minimum height=4em}," );
    anhaengenAnDatei( $datei, "\n line/.style    ={draw, thick, -latex’,shorten >=2pt}" );
    anhaengenAnDatei( $datei, "\n ]" );

    anhaengenAnDatei( $datei, "\n\matrix [column sep=5mm,row sep=7mm]" );
    anhaengenAnDatei( $datei, "\n{" );
    $seitenVol=12;
    $i=1;
    $f=false;
    foreach( $forkAutomat[$wZu] as $include )
    {
      if( $i < $limit )
      {
        ++$i;
        continue;
      }
      anhaengenAnDatei( $datei, "\n% row $i" );
      anhaengenAnDatei( $datei, "\n\\node [block] ($i)     " );
      anhaengenAnDatei( $datei, "{" );
      anhaengenAnDatei( $datei, "$include" );
      anhaengenAnDatei( $datei, "}" );
      anhaengenAnDatei( $datei, "; & \\\\" );
      ++$i;
      if( $limit < $i - $seitenVol )
      { // mehr als 12 gehen nicht auf eine Seite
        $f=true;
        $limit=$i-1;
        break;
      }
    }
    $stop=$i-1;
    anhaengenAnDatei( $datei, "\n};" );
    $i=1;
    foreach( $forkAutomat[$wZu] as $include )
    {
      if( $i < $limit )
      {
        ++$i;
        continue;
      }
      $j = $i + 1;
      if( $stop < $j )
        break;
      anhaengenAnDatei( $datei, "\n\draw [->,black,thick] ($i.south) -- ($j.north) node [right,midway] { };" );
      ++$i;
    }

  }
  anhaengenAnDatei( $datei, "\n\end{tikzpicture}\n" );
  if( isset($_REQUEST["fTest"]) )
    anhaengenAnDatei( $datei, "\end{document}\n" );
  anhaengenAnDatei( $datei, "\n" );
}
else if( isset($forkAutomat[$wZu]) )
{
  foreach( $forkAutomat[$wZu] as $include )
  {
    logForkedModul($include);
    include($include);
  }
}
else
{
  ?>Zustand '<?php echo $wZu;?>' unbekannt.<?php
}
if( isset($_REQUEST["forkdocC"]) )
{
?><P><?php
  $href=$DOC_WEBALIAS . "fork" . $docIdx . ".tex";
?>
<table border=1>
<tr>
<th colspan=2>
generierte SW-Doku
</th>
<tr>
<td>
<?php
  echo"<A HREF=\"$href\">.tex</A>";
?>
</td>
<td>
<?php
      $href=$DOC_ROOT . "fork" . $docIdx . ".tex";
      echo"<A HREF=\"./eiZu.php?wZu=loeschendDatei&file=$href\">l&ouml;schen</A>";
?>
</td>
</tr>
<?php
  if( isset($_REQUEST["fTest"]) )
  {
    $cmd = "/usr/bin/pdflatex -output-directory $DOC_ROOT $datei";
    $str = exec($cmd);
    $freigegeben = str_replace( "tex", "pdf", $datei );
    if( true == ($arrInfo = stat( $freigegeben) ) )
    {
?>
<tr>
<td>
<?php
      $href=$DOC_WEBALIAS . "fork" . $docIdx . ".pdf";
      echo"<A HREF=\"$href\">.pdf</A>";
?>
</td>
</tr>
<?php
    }
  }
?>
</table>
<?php
}
?>
</BODY>
</HTML>
<?php
exit;
?>
