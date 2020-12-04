<?php
if( !isset( $fPlausi ) )
{
?>
<script language=javascript type='text/javascript'>
<!--

function evalDate( wert )
{
  datum=true
  tag = wert.split("." )[0]
  if( 1 == tag.length )
    tag = "0" + tag;
  else if( 2 < tag.length )
    datum=false
  monat = wert.split("." )[1]
  if( 1 == monat.length )
    monat = "0" + monat;
  else if( 2 < monat.length )
    datum=false
  jahr = wert.split("." )[2]
  if( 1 == jahr.length )
    jahr = "0" + jahr;
  else if( 4 == jahr.length )
    jahr = jahr.charAt(2) + jahr.charAt(3);
  else if( 3 == jahr.length )
    datum=false
  else if( 4 < jahr.length )
    datum=false
  for( i=0; i<2; i++ )
    if( tag.charAt(i) < "0" || tag.charAt(i) > "9" || monat.charAt(i) < "0" || monat.charAt(i) > "9" || jahr.charAt(i) < "0" || jahr.charAt(i) > "9" )
      datum=false
  if( tag.charAt(0) == "0" && tag.charAt(1) == "0" )
    datum=false
  else if( tag.charAt(0) == "3" && tag.charAt(1) > "1" )
    datum=false
  else if( monat.charAt(0) == "0" && monat.charAt(1) == "0" )
    datum=false
  else if( monat.charAt(0) == "1" && monat.charAt(1) > "2" )
    datum=false
  else if( tag.charAt(0) > "3" || monat.charAt(0) > "1" )
    datum=false
  now = new Date
  jj = now.getYear() + 1900
  jahr = 20 + jahr
  if( (jj - jahr) > 1 )
  { // wg. Jahreswechsel 1 Jahr Toleranz
    datum=false
  }
  if( false == datum )
  {
    alert( "Das Datum " + wert + " ist fehlerhaft" )
    return false
  }
  datum = tag + '.' + monat + '.' + jahr
  return true
}
//Die folgenden trim-Funktionen stammen von http://www.evocomp.de/beispiele/javascript/trim.html
// Führende und Abschließende Whitespaces (Leerzeichen, Tabulatoren, ...)
// aus der übergebenen Zeichenkette entfernen.
function trim (zeichenkette) {
  // Erst führende, dann Abschließende Whitespaces entfernen
  // und das Ergebnis dieser Operationen zurückliefern
  return zeichenkette.replace (/^\s+/, '').replace (/\s+$/, '');
}

// Methode ltrim (left trim) zum String-Objekt hinzufügen
// Diese Methode löscht, ausgehend vom Anfang der Zeichenkette,
// alle Zeichen, die bei deren Vorkommen entfernt werden sollen.
// Der Parameter clist ist optional und gibt eine Liste von Zeichen vor,
// die von der Methode herausgelöscht werden sollen.
// Wird dieser Parameter nicht übergeben, so werden alle Whitespaces
// gelöscht, die am Anfang des Strings stehen.
String.prototype.ltrim = function (clist) {
  // Wurde eine Zeichenkette mit den zu entfernenden
  // Zeichen übergeben?
  if (clist)
    // In diesem Fall sollen nicht Whitespaces, sondern
    // alle Zeichen aus dieser Liste gelöscht werden,
    // die am Anfang des Strings stehen.
    return this.replace (new RegExp ('^[' + clist + ']+'), '');
  // Führende Whitespaces aus dem String entfernen
  // und das resultierende String zurückgeben.
  return this.replace (/^\s+/, '');
}

// Die Methode rtrim (right trim) erweitert ebenfalls das String-Objekt.
// Im Gegensatz zu ltrim wird hier aber vom Ende des Strings ausgegangen.
// Es werden also alle Whitespaces bzw. die Zeichen aus der übergebenen
// Zeichenliste gelöscht, die am Ende des Strings stehen.
String.prototype.rtrim = function (clist) {
  // Zeichenkette mit den zu entfernenden Zeichen angegeben?
  if (clist)
    // Zeichen aus der Liste, die am Ende des String stehen
    // löschen.
    return this.replace (new RegExp ('[' + clist + ']+$'), '');
  // Whitespaces am Ende des Strings ertfernen und dann das Ergebnis
  // dieser Operation zurückgeben.
  return this.replace (/\s+$/, '');
}

// Implementierung einer JavaScript trim Function als Erweiterung
// des vordefinierten JavaScript String-Objekts.
// Die Methode bedient sich den zuvor definierten Methoden ltrim
// und rtrim und kombiniert diese miteinander.
// Mit dem Parameter clist kann man auch hier eine Liste von Zeichen
// angeben, die vom Anfang, wie auch vom Ende der Zeichenkette entfernt
// werden soll.
String.prototype.trim = function (clist) {
  // Wird der Parameter clist angegeben, so werden statt der Whitespaces
  // die in dieser Variablen angegebenen Zeichen "getrimmt".
  if (clist)
    // Führende und abschließende Zeichen aus der Liste entfernen.
    return this.ltrim (clist).rtrim (clist);
  // Whitespaces vom Anfang und am Ende entfernen
  return this.ltrim ().rtrim ();
};

function pruefenEingaben(frm)
{
  if( frm.name == "frmAuftragabrechnung" )
  {
/* zum Kopieren:
    if( frm..value == "" ) {
      alert("Geben Sie die ...nummer an")
      frm..focus()
      return false
    }
*/
    if( frm.Auftragabrechnung_real_Zahlungsempfehlung.value == "" ) {
      alert("Tragen Sie Ihre Zahlungsempfehlung ein")
      frm.Auftragabrechnung_real_Zahlungsempfehlung.focus()
      return false
    }
    else if( frm.Auftragabrechnung_real_Zahlungsempfehlung.value == "1,00" ) {
      alert("Die Zahlungsempfehlung von einem Euro glaub ich nicht")
      frm.Auftragabrechnung_real_Zahlungsempfehlung.focus()
      return false
    }
    else if( frm.Auftragabrechnung_real_Zahlungsempfehlung.value == "1" ) {
      alert("Die Zahlungsempfehlung von einem Euro glaub ich nicht")
      frm.Auftragabrechnung_real_Zahlungsempfehlung.focus()
      return false
    }
    else {
      // 1. Dezimalstelle? zu Komma machen
      var str = frm.Auftragabrechnung_real_Zahlungsempfehlung.value
      var len = str.length
      if( '.' == str.charAt(len-3) )
      {
        var sLinks = str.substring(0,str.length-3)
        str = sLinks + ',' + str.charAt(len-2) + str.charAt(len-1)
      }
      // 2. alle Punkte ausm Rest loeschen
      str = str.replace(/\./g, "" )
      frm.Auftragabrechnung_real_Zahlungsempfehlung.value = str
    }
    if( frm.Auftragabrechnung_real_ForderungVN.value == "" ) {
      alert("Geben Sie die Forderung des VN an")
      frm.Auftragabrechnung_real_ForderungVN.focus()
      return false
    }
    else if( frm.Auftragabrechnung_real_ForderungVN.value == "1" ) {
      alert("Die Forderung von einem Euro glaub ich nicht")
      frm.Auftragabrechnung_real_ForderungVN.focus()
      return false
    }
    else if( frm.Auftragabrechnung_real_ForderungVN.value == "1,00" ) {
      alert("Die Forderung von einem Euro glaub ich nicht")
      frm.Auftragabrechnung_real_ForderungVN.focus()
      return false
    }
    else {
      // 1. Dezimalstelle? zu Komma machen
      var str = frm.Auftragabrechnung_real_ForderungVN.value
      var len = str.length
      if( '.' == str.charAt(len-3) )
      {
        var sLinks = str.substring(0,str.length-3)
        str = sLinks + ',' + str.charAt(len-2) + str.charAt(len-1)
      }
      // 2. alle Punkte ausm Rest loeschen
      str = str.replace(/\./g, "" )
      frm.Auftragabrechnung_real_ForderungVN.value = str
    }
    tag = frm.Termin.value.split("." )[0]
    if( 1 == tag.length )
      tag = "0" + tag;
    monat = frm.Termin.value.split("." )[1]
    if( 1 == monat.length )
      monat = "0" + monat;
    jahr = frm.Termin.value.split("." )[2]
    if( 1 == jahr.length )
      jahr = "0" + jahr;
    else if( 4 == jahr.length )
      jahr = jahr.charAt(2) + jahr.charAt(3);
    datum=true
    for( i=0; i<2; i++ )
      if( tag.charAt(i) < "0" || tag.charAt(i) > "9" || monat.charAt(i) < "0" || monat.charAt(i) > "9" || jahr.charAt(i) < "0" || jahr.charAt(i) > "9" )
    datum=false
    frm.Termin.value = tag + '.' + monat + '.' + jahr
    if( false == datum )
    {
      alert( "Das Datum " + frm.Termin.value + " ist fehlerhaft" )
      frm.Termin.focus()
      return false
    }
  }
  else if( frm.name == "frmTermin" )
  {
    if( 1 == selTA.options[selTA.selectedIndex].value )
    {
      kursNr = frm.Termin_string_Kuerzel.value.split(" " )[1]
      if( typeof kursNr === "undefined" )
      {
        alert( 'Leerzeichen muss zwischen Ort und Kurs-Nr!' )
        return false;
      }
    }
  }
  else if( frm.name == "frmProband" )
    {
    if( frm.Proband_string_Name.value == "" ) {
      alert("Wie heißt denn der Proband?")
      frm.Proband_string_Name.focus()
      return false
    }
  }
  else if( frm.name == "frmProbandOrt" )
    {
    if( frm.ProbandOrt_string_Ort.value == "" ) {
      alert("Wo wohnt denn der Proband?")
      frm.ProbandOrt_string_Ort.focus()
      return false
    }
  }
  else if( frm.name == "frmTel" )
  {
    if( frm.Tel_string_Tel.value == "" ) {
      alert("Offenbar gibt es keine Telefonnummer?")
      frm.Tel_string_Tel.focus()
      return false
    }
  }
  else if( frm.name == "frmMail" )
  {
    if( frm.Mail_string_Mail.value == "" ) {
      alert("Offenbar gibt es keine Mail-Adresse?")
      frm.Mail_string_Mail.focus()
      return false
    }
  }
  else if( frm.name == "frmTerminart" )
  {
    if( frm.Terminart_string_Terminart.value == "" ) {
      alert("Leere Terminart, ist das Ihr Ernst?")
      frm.Terminart_string_Terminart.focus()
      return false
    }
  }
  else if( frm.name == "frmSondertermin" )
  {
    if( frm.Sondertermin_date_Sondertermin.value == "" ) {
      alert("Geben Sie ein Datum ein")
      frm.Sondertermin_date_Sondertermin.focus()
      return false
    }
    if( false == evalDate( frm.Sondertermin_date_Sondertermin.value ) ) {
      frm.Sondertermin_date_Sondertermin.focus()
      return false
    }
//    else {
//	frm.Erstkontakt_date_Erstkontakt.value = trim(frm.Erstkontakt_date_Erstkontakt.value)
  //    return true
    //}
  }
else if( frm.name == "frmAktennotiz" )
  {
    if( !frm.Aktennotiz_string_an.value.localeCompare("SB") )
    {  
      if( -1 < frm.Aktennotiz_blob_Notiz.value.indexOf("€") )
      {
        str = frm.Aktennotiz_blob_Notiz.value.replace( /€/g, "EUR" )
        frm.Aktennotiz_blob_Notiz.value = str
        return false
      }
      else
	return true
    }
    if( false == evalDate( frm.Aktennotiz_date_Datum.value ) ) {
      frm.Aktennotiz_date_Datum.focus()
      return false
    }
    else {
	frm.Aktennotiz_date_Datum.value = trim(frm.Aktennotiz_date_Datum.value)
    }
    if( frm.Aktennotiz_date_zuErledigenBis.value == "" ) {
      alert("Geben Sie das zuErledigenBis Ihrer Aktennotiz an")
      frm.Aktennotiz_date_zuErledigenBis.focus()
      return false
    }
    if( false == evalDate( frm.Aktennotiz_date_zuErledigenBis.value ) ) {
      frm.Aktennotiz_date_zuErledigenBis.focus()
      return false
    }
    else {
	frm.Aktennotiz_date_zuErledigenBis.value = trim(frm.Aktennotiz_date_zuErledigenBis.value)
    }
//    if( frm.Aktennotiz_date_Datum.value > frm.Aktennotiz_date_zuErledigenBis.value ) { // funktioniert nicht
  //    alert( "Die Wiedervorlage muss nach der Erstellung dieser Notiz sein" )
   //   frm.Aktennotiz_date_zuErledigenBis.focus()
    //  return false
    return true
  }
  else if( frm.name == "frmDebitor" )
  {
    if( frm.Debitor_int_Konto.value == "" ) {
      alert("Geben Sie die Kontonummer des Debitors an")
      frm.Debitor_int_Konto.focus()
      return false
    }
  }
  else if( frm.name == "frmIndividualabrechnung" )
  {
//    if( ((frm.SELECTSL2.value == 15) || (frm.SELECTSL2.value > 17 && frm.SELECTSL2.value < 25) || (frm.SELECTSL2.value > 5 && frm.SELECTSL2.value < 14)) ) {
    //if( ((frm.SELECTSL2.value == 15) || (frm.SELECTSL2.value > 17 && frm.SELECTSL2.value < 25) || (frm.SELECTSL2.value > 5 && frm.SELECTSL2.value < 14)) && (frm.Individualabrechnung_string_DurchlaufGutschrift.value == "Quote") ) {
      //alert("Ein Vorschuss braucht den Durchlauf 100% in der Sammelgutschrift")
      //frm.Individualabrechnung_real_Summe.focus()
      //return false
    //}
    if( frm.Individualabrechnung_real_Summe.value == "1,00" ) {
      alert("Die Summe von einem Euro glaub ich nicht")
      frm.Individualabrechnung_real_Summe.focus()
      return false
    }
    else if( frm.Individualabrechnung_real_Summe.value == "1" ) {
      alert("Die Summe von einem Euro glaub ich nicht")
      frm.Individualabrechnung_real_Summe.focus()
      return false
    }
    else if( frm.Individualabrechnung_real_Summe.value == "0,00" ) {
      alert("Ein Eintrag von 0 Euro ist nicht notwendig, danke")
      frm.Individualabrechnung_real_Summe.focus()
      return false
    }
    else if( frm.Individualabrechnung_real_Summe.value == "0" ) {
      alert("Ein Eintrag von 0 Euro ist nicht notwendig, danke")
      frm.Individualabrechnung_real_Summe.focus()
      return false
    }
  }
  else if( frm.name == "frmKreditor" )
  {
    if( frm.Kreditor_int_Konto.value == "" ) {
      alert("Geben Sie die Kontonummer des Kreditors an")
      frm.Kreditor_int_Konto.focus()
      return false
    }
  }
  else if( frm.name == "frmRechnungStorno" )
  {
    if( frm.RechnungStorno_blob_Stornierungsgrund.value == "" ) {
      alert("Geben Sie den Grund der Stornierung an")
      frm.RechnungStorno_blob_Stornierungsgrund.focus()
      return false
    }
  }
  else if( frm.name == "frmEDV" )
  {
    if( frm.EDV_real_Angebot.value == "" ) {
	frm.EDV_real_Angebot.value = "0";
      return true
    }
  }
  else if( frm.name == "frmPortal" )
  {
    if( frm.Portal_string_PLZ.value == "" ) {
      alert("Geben Sie eine PLZ an")
      frm.Portal_string_PLZ.focus()
      return false
    }
    else if( frm.Portal_string_SchadenNr.value == "" ) {
      alert("Geben Sie einen SchadenNr an")
      frm.Portal_string_SchadenNr.focus()
      return false
    }
    else if( frm.Portal_string_Besichtigungsort.value == "" ) {
      alert("Geben Sie einen Besichtigungsort an")
      frm.Portal_string_Besichtigungsort.focus()
      return false
    }
    else if( frm.Portal_string_vnName.value == "" ) {
      alert("Geben Sie den Namen des VN an")
      frm.Portal_string_vnName.focus()
      return false
    }
  }
  else if( frm.name == "frmFixum" )
  {
    if( frm.Fixum_real_Fixum.value == "1" ) {
      alert("Das Fixum von einem Euro glaub ich nicht")
      frm.Fixum_real_Fixum.focus()
      return false
    }
  }	
  else if( frm.name == "frmVersicherer" )
  {
    str =  frm.Versicherer_string_Versicherer.value;
    if( !str.replace(/\s/g, '').length ) {
      alert("Wie schreibt sich denn der neue Versicherer?")
      frm.Versicherer_string_Versicherer.focus()
      return false
    }
  }
  return true
}
// -->
</script>
<?php
}
?>
