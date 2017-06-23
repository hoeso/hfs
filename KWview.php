<?php
require_once("KWmodel.php");
include("vektorQuart.prj"); // $quart
class KWview extends KWmodel
{
  protected $tag;

  function __construct($strDate, $filter="")
  {
    parent::__construct($strDate, $filter);
    //var_dump($this->tag); echo "\n<br>";
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return parent::__get('Datum');
      case 'DatumEU':
        return parent::__get('DatumEU');
      case 'Go':
        return parent::__get('Go');
      case 'Jahr':
        return parent::__get('Jahr');
      case 'Kalenderwoche':
        return parent::__get('Kalenderwoche');
      case 'KWweiter':
        return parent::__get('KWweiter');
      case 'KWzurueck':
        return parent::__get('KWzurueck');
      case 'Stop':
        return parent::__get('Stop');
      case 'WochentagNumerisch':
        return parent::__get('WochentagNumerisch');
      default:
        throw new Exception("KWview hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function show( $what, $how='initialen' )
  {
    global $quart;
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    if( 'client' <> $what and 'mitarbeiter' <> $what )
    {
      dEcho( $b_, "KWview::show( [client|mitarbeiter] )" );
      return;
    }
    $title = "zur ";
    if( 'client' == $what )
    {
      $title .= 'Mitarbeiter&#042;innen';
      $maORcl = "d"; // alles was nicht c ist, ist MA
      $NOTmaORcl = "c"; // alles was nicht c ist, ist MA
    }
    else
    {
      $title .= 'Klient&#042;innen';
      $maORcl = "c";
      $NOTmaORcl = "d"; // alles was nicht c ist, ist MA
    }
    $title .= " Ansicht wechseln";
    if( 'client' == $what )
      $img = 'grandma-penguin-18px.png';
    else
      $img = 'threepeople-18px.png';
    ?><table><tr><?php
    if( 'initialen' == $how )
    {
      $text='n';
      if( 'client' == $what )
      {
        $concat = "CONCAT(LEFT(c.Name,1),LEFT(c.Vorname,1))";
      }
      else
      {
        $concat = "CONCAT(LEFT(m.Name,1),LEFT(m.Vorname,1))";
      }
    }
    else
    {
      $text='i';
      if( 'client' == $what )
      {
        $concat = "CONCAT(c.Name,' ',c.Vorname)";
      }
      else
      {
        $concat = "CONCAT(m.Name,' ',m.Vorname)";
      }
    }
    /*** 1. Header ausgeben           ***/
    $i=0;
    $ancor=0;
    $f="";
    if( isset($_REQUEST["f"]) ) // Filter auf Klient*in
      $f = "&f=" . $_REQUEST["f"];
    foreach ($this->tag as $dayofweek => $value)
    {
      /***
       *** if-Block gibt die Symbole aus ueber der Wochentag-Zeile
       ***/
      if( !$i )
      { // Pics der Umschalter Client o. MA
        ++$ancor;
        $NOTkw = $kw = $this->Kalenderwoche;
        if( 'c' == $maORcl )
        {
	  $kw .= " Klient";
	  $NOTkw .= " MA";
	  $kwTitel  = " MA";
        }
	else
        {
	  $kw .= " MA";
	  $NOTkw .= " Klient";
	  $kwTitel  = " Klient";
        }
	if( isset($_REQUEST['d']) )
	  $d="&d";
	else
	  $d="";
        ?><td colspan=8>
	<!--img class="img18" src="images/punaise-18px.png" alt="diese Uhrzeit" usemap="#pinnen<?php echo $ancor;?>"-->
	<img class="img18" src="images/reload-icon-18px.png" alt="hier neu laden" usemap="#pinnen<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="pinnen<?php echo $ancor;?>">
        <!--area shape=rect coords="0,0,18,18" title='diese Uhrzeit pinnen' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $NOTkw; echo $f;?>#<?php echo $ancor;?>"-->
        <area shape=rect coords="0,0,18,18" title='Kalender neu laden' href="javascript:location.reload()" target="_self">
        </map>
	<img class="img18" src="images/<?php echo $img;?>" alt="zum Wochenplan" usemap="#maorcl<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="maorcl<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='<?php echo $title;?>' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw;?>#<?php echo $ancor;?>">
        </map>
	<img class="img18" src="images/Copy-18px.png" alt="KW kopieren" usemap="#kopierenKW<?php echo $ancor;?>">
        <map name="kopierenKW<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" target="_blank" title='KW<?php echo $this->Kalenderwoche;?> kopieren' href="./mn.php?mn=kopierenKW&a=Kalenderwoche&sl=4&sl1=Jahr-%3E&sl2=KW-%3E&sl3=Jahr&sl4=KW&b=<?php echo $maORcl;?>&j=<?php echo $this->Jahr . $d;?>&k=<?php echo $this->Kalenderwoche;?>&navi=KW&u=<?php echo $this->Kalenderwoche;?>%20-&gt;KW%3F&kopierenKW_x#<?php echo $ancor;?>">
        </map>
        <!--a class="img18" href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=Y-m-d&navi=KW&u=<?php echo $this->DatumEU . " " . $NOTkw;?>#<?php echo $ancor;?>">Heute</a-->
        <img class="img18" src="images/jean-victor-balin-arki-arrow-left-18px.png" alt="zur&uuml;ck" usemap="#zurueck<?php echo $ancor;?>">
        <map name="zurueck<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche - 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWzurueck;?>&navi=KW&u=<?php echo $kw - 1 . " " . $kwTitel; echo $f;?>#<?php echo $ancor;?>">
        </map>
        <!--em class="img18"><a href="./cal.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&c=<?php echo $text;?>&navi=KW&u=<?php echo $this->Kalenderwoche . " " . $kwTitel; echo $f;?>#<?php echo $ancor;?>">KW<?php echo $this->Kalenderwoche;?></a></em-->
        <em class="img18">
	<div class="dropdown">
	<button class="dropbtn">KW<?php echo $this->Kalenderwoche;?></button>
	  <div class="dropdown-content">
	    <?php
	    $f="";
            if( isset($_REQUEST["f"]) ) // Filter auf Klient*in
              $f = "&f=" . $_REQUEST["f"];
	    $kw_ = new KW( "Y-m-d", $f );
	    for( $wk=$kw_->Kalenderwoche; $wk < 54; $wk++ )
	    {
              ?><a href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $kw_->Datum;?>&navi=KW&u=<?php echo $wk . " " . $kwTitel; echo $f;?>#<?php echo $ancor;?>"><?php echo $kw_->DatumEU . "  [$wk]";?></a><?php
	      $kw_ = new KW( $kw_->KWweiter, $f );
	    }?>
          </div>
	</div>
	</em>
        <img class="img18" src="images/jean-victor-balin-arki-arrow-right-18px.png" alt="weiter" usemap="#weiter<?php echo $ancor;?>">
        <map name="weiter<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche + 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWweiter;?>&navi=KW&u=<?php echo $kw + 1 . " " . $kwTitel; echo $f;?>#<?php echo $ancor;?>">
        </map><?php
        if( 'initialen' == $how )
          $img2 = "1430954247-18px.png";
        else
          $img2 = "matt-icons_emblem-minus-18px.png";?>
	<img class="img18" src="images/<?php echo $img2;?>" alt="Darstellung" usemap="#initialen<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="initialen<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='Darstellung' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&c=<?php echo $text;?>&navi=KW&u=<?php echo $this->Kalenderwoche . " " . $kwTitel; echo $f;?>#<?php echo $ancor;?>">
        </map>
	<img class="img18" src="images/kalender-18px.png" alt="Wochen&uuml;bersicht" usemap="#woche<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="woche<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" target="_blank" title='Wochen&uuml;bersicht' href="./mn.php?mn=blatt&navi=KW&a=<?php echo $this->Kalenderwoche;?>&c=k&k=<?php echo $this->Datum;?>&u=KW<?php echo $this->Kalenderwoche; echo $f;?>#<?php echo $ancor;?>">
        </map>
	<img class="img18" src="images/calendar2-18px.png" alt="Monats&uuml;bersicht" usemap="#monat<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="monat<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" target="_blank" title='Monats&uuml;bersicht' href="./mn.php?mn=blatt&navi=KW&a=<?php echo $this->Kalenderwoche;?>&k=<?php echo $this->Datum;?>&c=m&u=KW<?php echo $this->Kalenderwoche; echo $f;?>#<?php echo $ancor;?>">
        </map><?php
	$js_str="onchange=\"javascript:self.location='./mn.php?mn=kw&navi=KW&a=MAClientVS&b=" . $NOTmaORcl . "&k=" . $this->Datum . "&u=" . $NOTkw . "&fKeinUpdate=true&f=' + this.options[this.selectedIndex].value; return true;\"";
        $dim=0;
        unset($a);
        if( 'client' == $what )
          $this->gibClients( $a, $dim );
        else
          $this->gibMAs( $a, $dim );
        if( $a[0]==0 && $a[1]==1 ){}
        else
        {?>
          <FORM ACTION='./mn.php'>
          <INPUT TYPE=HIDDEN NAME='mn' VALUE='kw'>
          <INPUT TYPE=HIDDEN NAME='navi' VALUE='KW'>
          <INPUT TYPE=HIDDEN NAME='a' VALUE='MAClientVS'>
          <INPUT TYPE=HIDDEN NAME='b' VALUE='<?php echo $NOTmaORcl;?>'>
          <INPUT TYPE=HIDDEN NAME='k' VALUE='<?php echo $this->Datum;?>'>
          <INPUT TYPE=HIDDEN NAME='u' VALUE='<?php echo $NOTkw;?>'>
          <INPUT TYPE=HIDDEN NAME='fKeinUpdate' VALUE='true'>
          <!--INPUT TYPE=HIDDEN NAME='docC' VALUE='57.8.1'-->
          <SELECT NAME='f' <?php echo $js_str;?> SIZE='1'>
      		  <OPTION VALUE='0'>-- alle --
          <?php
          for( $i=0; $i<count($a); $i += $dim )
          {
            $i1 = $i+1;
            echo"\n<OPTION VALUE='$a[$i]'";
      	    if( isset($_REQUEST['f']) and $a[$i] == $_REQUEST['f'] )
      	      echo " SELECTED";
	    ?>><?php
            if( 'client' <> $what )
	    { // MA KW-Restkontigent berechnen
	      echo $this->gibKontingent( $a[$i], $this->Datum ) - $this->gibKontingentKW( $a[$i], $this->Jahr, $this->Kalenderwoche ) . " - ";
	    }
      	    echo"$a[$i1]";
          }
          ?></SELECT><?php
          if( isset($_REQUEST["d"]) )
          {?>
            <INPUT TYPE=HIDDEN NAME='d'><?php
          }/*?>
          <INPUT TYPE=SUBMIT VALUE='go!'>
          </FORM><?php*/
        }?>
        </td></tr><tr><td></td><?php
        ++$i;
	continue;
      }?>
      <td><?php
      echo $dayofweek . " " . $value . "    ";
      ?></td><?php
      ++$i;
      /***
       *** Ende der Symbol-Anzeige ueber der Wochentag-Zeile
       ***/
    }?>
    </tr><tr><?php
    /*** 2. Quart-Zeilen ausgeben     ***/
    $row = $this->Go;
    while( $row < $this->Stop )
    {
      $i=0;
      foreach ($this->tag as $dayofweek => $value)
      {
        if( !$i )
        { // Zeile mit Uhrzeit beginnen
          ?><td><?php echo "\n" . $quart[$row];?></td><?php
          ++$i;
	  continue;
        }
	?>
        <td><?php
        $dim=0;
        unset($a);
        $this->gibTermine( $a, $dim, $what, $concat, $dayofweek, $row );
        if( $a[0]==0 && $a[1]==1 && $a[2]==2 )
	{ // nix gfundn worn :-(
	  if( isset($_REQUEST['d']) )
	    $d="&d";
	  else
	    $d="";
          ?><a href="mn.php?mn=planend&a=ClientVS&sl=3&sl1=Client&sl2=<?php echo $row;?>&sl3=<?php echo $i;?>&navi=Plan&u=KW<?php echo $this->Kalenderwoche;?>&k=<?php echo $this->Kalenderwoche;?>&j=<?php echo $this->Jahr . $d;?>&planungVS_x" target="_blank" title="<?php echo $dayofweek . " " . $quart[$row];?>">&nbsp;</a><?php
          if( isset($clutch) && 1 < $i ) // 1 < $i: Vorgaenger 'Sonntag' weglassen
          {
            $c_ = explode( "|", $clutch );
            if( isset($_REQUEST["f"]) and $_REQUEST["f"] )
            {
	      ?> 
              <img class="img18" src="images/Copy-18px.png" alt="Termin kopieren" usemap="#kopierenVorgaenger<?php echo $maclientvsID;?>">
              <map name="kopierenVorgaenger<?php echo $maclientvsID;?>">
              <area shape=rect coords="0,0,18,18" target="_blank" title='Termin kopieren' href="./mn.php?mn=kopierenVorgaenger&a=MAClientVS&b=<?php echo $maclientvsID;?>&navi=KW&u=Termin%20kopieren%20KW<?php echo $this->Kalenderwoche;?>&kopierenVorgaenger_x#<?php echo $ancor;?>">
              </map><?php
	    }
          }
          unset($clutch);
	}
        else
	{ // Treffer, hier findet ein Client|MA Besuch statt:
          /*** zunaechst noch Bindestrich-Link fuer weiteren Einsatz um diese Uhrzeit anbieten: ***/
	  if( isset($_REQUEST['d']) )
	    $d="&d";
	  else
	    $d="";
          ?><a href="mn.php?mn=planend&a=ClientVS&sl=3&sl1=Client&sl2=<?php echo $row;?>&sl3=<?php echo $i;?>&navi=Plan&u=KW<?php echo $this->Kalenderwoche;?>&k=<?php echo $this->Kalenderwoche;?>&j=<?php echo $this->Jahr . $d;?>&planungVS_x" target="_blank" title="<?php echo $dayofweek . " " . $quart[$row];?>">&nbsp;</a><?php
	  for( $k=0; $k < count($a); $k += $dim )
	  {
            $maclientvsID=$a[$k+4];
	    $clutch = $dayofweek . $a[$k+1] . $quart[$row] . "|" . $a[$k+2] . "|" . $a[$k+3] . "|" . $a[$k+4] . "|" . $a[$k+5] . "|" . $a[$k+6];
	    if ( !isset($aSC) or isset($aSC) and !isset($aSC[$clutch]) )
	    { // Zelle assoziativ belegen: "Wochentag . [MA|Client]-Initialen" = Menge
	      $aSC[$clutch] = $a[$k];
	    }
	  }
	}
	if( isset($aSC) )
          foreach ($aSC as $sc => &$counter)
	  {
            if( isset($_REQUEST["d"]) )
              dEcho( $b_, $sc );
	    if( substr($sc,0,2) == $dayofweek )
	    { // wir sind im richtigen Wochentag(=Spalte)
              $a__ = explode( "|", $sc );
              if( 'client' == $what )
	      {
	        $ent=$a__[5];
                $str="&a=Client&planungTag_x&k=c"; // k=c: eOverlay-Kontext --> ClientVS=Client
                $str.="&l=zum%20Klient&#42;in";
	      }
              else                
	      {
	        $ent=$a__[3];
                $str="&a=MA&planungMA_x";
                $str.="&l=zum%20MA&#42;in";
	      }
              ?><a href="mn.php?mn=3653&navi=Plan&ID=<?php echo $a__[2];?>&u=<?php echo substr($sc,2,2) . $str;?>&MAClientVS=<?php echo $ent;?>#<?php echo $ent;?>" target="_blank" title=<?php echo $a__[1] . ">"; // title: voller Name
              if( 'initialen' == $how )
	        echo substr($sc,2,2) . " "; // nur die Initialen
              else
	        echo substr($a__[1],0,12) . "[" . $a__[4] . "] "; // Name Vorname
              if( 'mitarbeiter' == $what )
	      {
	        $md_ = explode( ".", $value );
		for( $n=0; $n < 2; $n++ ) // fuer fuehrende Null sorgen:
  		  if( 1 == strlen($md_[$n]) )
		    $md_[$n] = "0$md_[$n]";
	        //echo "-$a__[2] + 20$this->Jahr-$md_[1]-$md_[0]";
		$maPraesenz = new MAAbwesenheit( "20$this->Jahr", "20$this->Jahr-$md_[1]-$md_[0]", $a__[2] );
                if( true == $maPraesenz->abwesend )
                {
                  ?>&nbsp;&nbsp;<img title="<?php echo $maPraesenz->vonBis;?>" src="images/<?php
                  if( "krank" == $maPraesenz->Status )
                    echo "krank";
          	  else
                    echo "havaianas07";
                  ?>-18px.png"><?php
                }
                unset($maPraesenz);
	      }
              ?></a><?php
	      if( $counter )
	        --$counter;
	      if( !$counter )
	        unset($aSC[$sc]);
            }
	  }
        ?></td><?php
        ++$i;
      }?>
      </tr><tr><?php
      /*** alle 20 Zeilen Header wieder einfuegen ***/
      if( !($row % 20) )
      {
        $j=0;
        foreach ($this->tag as $cltch => $datm)
        {
          if( !$j )
          {
            ++$ancor;
	    $NOTkw = $kw = $this->Kalenderwoche;
            if( 'c' == $maORcl )
            {
	      $kw .= " Klient";
	      $NOTkw .= " MA";
	      $kwTitel  = " MA";
            }
	    else
            {
	      $kw .= " MA";
	      $NOTkw .= " Klient";
	      $kwTitel  = " Klient";
            }
	    ?><td colspan=8>
	    <!--img class="img18" src="images/punaise-18px.png" alt="diese Uhrzeit" usemap="#pinnen<?php echo $ancor;?>"-->
	    <img class="img18" src="images/reload-icon-18px.png" alt="hier neu laden" usemap="#pinnen<?php echo $ancor;?>">
	    <a name='<?php echo $ancor;?>'></a>
            <map name="pinnen<?php echo $ancor;?>">
            <!--area shape=rect coords="0,0,18,18" title='diese Uhrzeit pinnen' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $NOTkw;?>#<?php echo $ancor;?>"-->
            <area shape=rect coords="0,0,18,18" title='Kalender neu laden' href="javascript:location.reload()" target="_self">
            </map>
	    <img class="img18" src="images/<?php echo $img;?>" alt="zum Wochenplan" usemap="#maorcl<?php echo $ancor;?>">
            <a name='<?php echo $ancor;?>'></a>
            <map name="maorcl<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='<?php echo $title;?>' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw;?>#<?php echo $ancor;?>">
            <img class="img18" src="images/Copy-18px.png" alt="KW kopieren" usemap="#kopierenKW<?php echo $ancor;?>">
            <map name="kopierenKW<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" target="_blank" title='KW<?php echo $this->Kalenderwoche;?> kopieren' href="./mn.php?mn=kopierenKW&a=Kalenderwoche&sl=4&sl1=Jahr-%3E&sl2=KW-%3E&sl3=Jahr&sl4=KW&b=<?php echo $maORcl;?>&j=<?php echo $this->Jahr . $d;?>&k=<?php echo $this->Kalenderwoche;?>&navi=KW&u=<?php echo $this->Kalenderwoche;?>%20-&gt;KW%3F&kopierenKW_x#<?php echo $ancor;?>">
            </map>
            <!--a class="img18" href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=Y-m-d&navi=KW&u=<?php echo $this->DatumEU . " " . $NOTkw;?>#<?php echo $ancor;?>">Heute</a-->
            <img class="img18" src="images/jean-victor-balin-arki-arrow-left-18px.png" alt="zur&uuml;ck" usemap="#zurueck<?php echo $ancor;?>">
            <map name="zurueck<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche - 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWzurueck;?>&navi=KW&u=<?php echo $kw - 1 . " " . $kwTitel;?>#<?php echo $ancor;?>">
            </map>
            <!--em class="img18">KW<?php echo $this->Kalenderwoche;?></em-->
            <em class="img18">
      	      <div class="dropdown">
      	      <button class="dropbtn">KW<?php echo $this->Kalenderwoche;?></button>
      	      <div class="dropdown-content">
      	      <?php
      	      $f="";
              if( isset($_REQUEST["f"]) ) // Filter auf Klient*in
                $f = "&f=" . $_REQUEST["f"];
      	      $kw_ = new KW( "Y-m-d", $f );
      	      for( $wk=$kw_->Kalenderwoche; $wk < 54; $wk++ )
      	      {
                ?><a href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $kw_->Datum;?>&navi=KW&u=<?php echo $wk . " " . $kwTitel; echo $f;?>#<?php echo $ancor;?>"><?php echo $kw_->DatumEU . "  [$wk]";?></a><?php
      	        $kw_ = new KW( $kw_->KWweiter, $f );
      	      }?>
              </div>
	    </div>
	    </em>
            <img class="img18" src="images/jean-victor-balin-arki-arrow-right-18px.png" alt="weiter" usemap="#weiter<?php echo $ancor;?>">
            <map name="weiter<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche + 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWweiter;?>&navi=KW&u=<?php echo $kw + 1 . " " . $kwTitel;?>#<?php echo $ancor;?>">
            </map>
    	    <img class="img18" src="images/<?php echo $img2;?>" alt="Darstellung" usemap="#initialen<?php echo $ancor;?>">
    	    <a name='<?php echo $ancor;?>'></a>
            <map name="initialen<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='Darstellung' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&c=<?php echo $text;?>&navi=KW&u=<?php echo $this->Kalenderwoche . " " . $kwTitel;?>#<?php echo $ancor;?>">
            </map>
	    <img class="img18" src="images/kalender-18px.png" alt="Wochen&uuml;bersicht" usemap="#woche<?php echo $ancor;?>">
	    <a name='<?php echo $ancor;?>'></a>
            <map name="woche<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" target="_blank" title='Wochen&uuml;bersicht' href="./mn.php?mn=blatt&navi=KW&a=<?php echo $this->Kalenderwoche;?>&c=k&k=<?php echo $this->Datum;?>&u=KW<?php echo $this->Kalenderwoche;?>#<?php echo $ancor;?>">
            </map><?php
	    $js_str="onchange=\"javascript:self.location='./mn.php?mn=kw&navi=KW&a=MAClientVS&b=" . $NOTmaORcl . "&k=" . $this->Datum . "&u=" . $NOTkw . "&fKeinUpdate=true&f=' + this.options[this.selectedIndex].value; return true;\"";
            $dim=0;
            unset($a);
            if( 'client' == $what )
              $this->gibClients( $a, $dim );
            else
              $this->gibMAs( $a, $dim );
            if( $a[0]==0 && $a[1]==1 ){}
            else
            {?>
              <FORM ACTION='./mn.php'>
              <INPUT TYPE=HIDDEN NAME='mn' VALUE='kw'>
              <INPUT TYPE=HIDDEN NAME='navi' VALUE='KW'>
              <INPUT TYPE=HIDDEN NAME='a' VALUE='MAClientVS'>
              <INPUT TYPE=HIDDEN NAME='b' VALUE='<?php echo $NOTmaORcl;?>'>
              <INPUT TYPE=HIDDEN NAME='k' VALUE='<?php echo $this->Datum;?>'>
              <INPUT TYPE=HIDDEN NAME='u' VALUE='<?php echo $NOTkw;?>'>
              <INPUT TYPE=HIDDEN NAME='fKeinUpdate' VALUE='true'>
              <!--INPUT TYPE=HIDDEN NAME='docC' VALUE='57.8.1'-->
              <SELECT NAME='f' <?php echo $js_str;?> SIZE='1'>
      	      	  <OPTION VALUE='0'>-- alle --
              <?php
              for( $i=0; $i<count($a); $i += $dim )
              {
                $i1 = $i+1;
                echo"\n<OPTION VALUE='$a[$i]'";
      	        if( isset($_REQUEST['f']) and $a[$i] == $_REQUEST['f'] )
      	        echo " SELECTED";
	        ?>><?php
                if( 'client' <> $what )
	        { // MA KW-Restkontigent berechnen
	          echo $this->gibKontingent( $a[$i], $this->Datum ) - $this->gibKontingentKW( $a[$i], $this->Jahr, $this->Kalenderwoche ) . " - ";
	        }
      	        echo"$a[$i1]";
              }
              ?></SELECT><?php
              if( isset($_REQUEST["d"]) )
              {?>
                <INPUT TYPE=HIDDEN NAME='d'><?php
              }/*?>
              <INPUT TYPE=SUBMIT VALUE='go!'>
              </FORM><?php*/
            }?>
            </td></tr><tr><td></td><?php
            ++$j;
            continue;
          }?>
          <td><?php
          echo $cltch . " " . $datm . "    ";
          ?></td><?php
          ++$j;
        }?>
        </tr><tr><?php
      }
      ++$row;
    }?>
    </tr></table><?php
  }
}
