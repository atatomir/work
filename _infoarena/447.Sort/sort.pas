var bufin:array[1..65000]of byte;
    n,i:longint;
    a:array[1..10001]of byte;
    nr1,nr2,nr3:longint;
    nr11,nr12,nr13:longint;
    nr21,nr22,nr23:longint;
    nr31,nr32,nr33:longint;
    min,cont:longint;

begin
  assign(input,'sort.in'); reset(input);
  assign(output,'sort.out'); rewrite(output);
  settextbuf(input,bufin);

  nr1 := 0;
  nr2 := 0;
  nr3 := 0;
  nr11 := 0;
  nr12 := 0;
  nr13 := 0;
  nr21 := 0;
  nr22 := 0;
  nr23 := 0;
  nr31 := 0;
  nr32 := 0;
  nr33 := 0;

  readln(n);
  case n of
    1: cont := 0;
    2:begin
        read(nr1,nr2) ;
        if nr1 > nr2 then
          cont := 1
        else
          cont := 0;
      end;
    else
    begin
      for i := 1 to n do
      begin
        read(a[i]);
        case a[i] of
          1: inc(nr1);
          2: inc(nr2);
          3: inc(nr3);
        end;
      end;

      for i := 1 to nr1 do
       case a[i] of
         1: inc(nr11);
         2: inc(nr12);
         3: inc(nr13);
       end;

      for i := 1 to nr2 do
        case a[i+nr1] of
          1: inc(nr21);
          2: inc(nr22);
          3: inc(nr23);
        end;

      for i := 1 to nr3 do
        case a[i+nr1+nr2] of
          1: inc(nr31);
          2: inc(nr32);
          3: inc(nr33);
        end;

      cont := 0;

      if nr12 < nr21 then min := nr12 else min := nr21;
      cont := cont + min;
      nr11 := nr11 + min;
      nr22 := nr22 + min;
      nr12 := nr12 - min;
      nr21 := nr21 - min;

      if nr13 < nr31 then min := nr13 else min := nr31;
      cont := cont + min;
      nr11 := nr11 + min;
      nr33 := nr33 + min;
      nr13 := nr13 - min;
      nr31 := nr31 - min;

      if nr23 < nr32 then min := nr23 else min := nr32;
      cont := cont + min;
      nr22 := nr22 + min;
      nr33 := nr33 + min;
      nr23 := nr23 - min;
      nr32 := nr32 - min;

      min := nr12 + nr13;
      cont := cont + 2*min;

    end;
  end;



  write(cont);

  close(input);
  close(output);
end.