1) odbiornik wysyła NAK co 10 sek przez 60 sek 

1.5) odbiornik wysyła
   NAK - wersja podstawowa
   C - wersja CRC
2) nadajnik rozpoczyna przesyłanie 1 bloku
    - blok - 128 bajtów. Wysyłany jest kolejny po otrzymaniu ACK poprzedniego
    - blok zaopatrywany jest w nagłówek: znak SOH, numer bloku (1 bajt), dopełnienia tego bloku do 255 (255 – numer bloku)
3) przesyłanie: nagłówek, blok, suma kontrolna

4) odbiornik odbiera, liczy własną sumę, porównuje z otrzymaną:
    - są różne - NACK - ponownie przesyłanie
    - zgadzają się - ACK - przesyła kolejny blok

5) po przesłaniu ostatniego bloku - EOT do otrzymania ACK

SOH 01H

EOT 04H

ACK 06H

NAK 15H

CAN 18H

C 	43H 
