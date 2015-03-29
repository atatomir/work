var nr1,nr2,i,j,n,suma,x:longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'secvente.in');  reset(input);
  assign(output,'secvente.out');  rewrite(output);
  settextbuf(input,bufin);

  for i := 1 to 3 do
  begin
    suma := 0; nr1 := 0; nr2 := 0;
    readln(n);

    for j := 1 to n do
    begin
      readln(x);
      suma := (suma + x) mod 3;
      x := x mod 3 ;
      case x of
        1: inc(nr1);
        2: inc(nr2);
      end;
    end;

    if suma =1 then
    begin
      suma := 0;
      if nr1 > 0 then
        n := n - 1
      else
        n := n - 2;
    end;

    if suma = 2 then
    begin
      suma := 0;
      if nr2 > 0 then
        n := n - 1
      else
        n := n - 2;
    end;


    writeln(n);
  end;


  close(input);
  close(output);
end.