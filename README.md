C++-ohjelmoinnin perusteet kussin lopputyö
Hotellin varausjäjestelmä

Oskari Järvinen

Ohjelma on tehty 5 arvosanan mukaisesti.
Ohjelmassa käyttöliittymä, kommentointi ja ohjelmointi ovat engalnniksi.

Perustoimminnot 4-5 varten:
- Ohjelma arpoo huoneita tarvittaessa parillinsen määrän väliltä 40–300, ja niistä puolet (alkupuoli) on yhden hengen ja puolet (loppupuoli) kahden hengen huoneita.
- Ohjelmassa on selkeä ja monipuolinen valikko käyttäjälle.
- Ohjelma suoriutuu jokaisesta ongelmatilanteesta jota kokeilin. Ohjelma ei kaatunut kertaakaan testauksieni aikana.
- Ohjelmassa käyttäjä voi:
  - Varata huoneita nimellä. Varattavat huoneet voi valita joko käyttäjä huoneen numeroilla tai arpomalla.
  - Etsiä huoneita nimellä
- Huoneiden hinnat ovat globaaleja const int, joten niitä voi vaihtaa tarvittaessa helposti
- Ohjelma arpoo varauksen yhdessä alennuksen huoneen hintaan
- Ohjelma ilmoittaa hinnan ennen varauksen tekemistä, jos huoneita on saatavilla
- Ohjelma ei anna tehdä varausta, jos huoneita ei ole saatavilla
- Ohjelmaa voi käyttää niin kauan kuin haluaa ja tilauksia voi tehdä niin monta kuin huoneita riittää
- Ohjelmassa on toteutettu suurimmaksi osaksi aliohjelmilla. Halusin itse kokeilla tehdä main ohjelman mahdollisimman lyhyeksi. int main on vain 3 linen pituinen.

Lisätoiminnot 5 toivossa:
- Ohjelma osaa lukea input.txt tiedostolta huoneiden määrän ja varauksen tilan, eli huoneita ei tarvitse joka kerta arpoa uudelleen.
- Ohjelma on tehty erittäin tarkasti minimoimaan käyttäjän virheen
- Ohjelmassa käyttäjä voi:
  - Tarkistaa montako kumpaakin huonetyypin huonetta on vapaana
	- Tarkistaa huoneen varauksen tilan huoneen numerolla
  - Tarkistaa jokaisen huoneen varauksen tilan samalla kertaa
  - Tarkistaa huoneiden hinnat (1hh 100€ ja 2hh 150€) ja alennukset (0%, 10% tai 20%)
- lopuksi kun käyttäjä poistuu (konsolia käyttäen) ohjelma tallentaa tiedot input.txt tiedostoon, jotta "samaan hotelliin" voidaan palata myöhemmin
- Ohjelmassa on hyödynnetty functions.h headeria.

Mahdolliset parannukset:
Tein ohjelman niin, että tulevaisuudessa siihen voi lisätä ominaisuuden varata monta huonetta monelle ihmiselle samalla kerralla.
Ohjelma osaisi itse tarkistaa tai mahdollisesti kysyä käyttäjältä montako kumpaakin huonetyyppiä varataan yhdessä tilauksessa (esim 10 henkinen perhe 5 2hh huonetta)
