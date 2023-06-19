READ ME

1/ użyta komenda systemowa do czyszczenia ekranu jest obsługiwana przez powłokę sh/ksh/bash
2/ input przyjmowany jest z klawiatury
3/ przez konstrukcje oczekiwania na znak ENTER czasami program prosi o podwójne wprowadzenie znaku (problem polegał na tym, że przy pojedynczym getchar wiadomość z funkcji system_out była wypisywana podwójnie i nie czekała na input gracza, co powodowało czyszczenie ekranu przedwcześnie)
4/ jeśli komputer wielokrotnie wyświetla informacje o celowaniu to znaczy, że warunek poprawnego strzału nie został spełniony i losuje ponownie.

