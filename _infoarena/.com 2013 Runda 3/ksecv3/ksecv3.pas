var n,k,i,x,cont:longint;
    suma,sumat:int64;
    r:array[1..100001]of longint;
    iesit:boolean;
    bufin:array[1..15000]of byte;
begin
  assign(input,'ksecv3.in'); reset(input);
  assign(output,'ksecv3.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  suma := 0;

  for i := 1 to n do
  begin
    read(x);
    suma := suma + x;
  end;


  close(input);
  assign(input,'ksecv3.in'); reset(input);
  readln();                 cont := 0;    iesit := false;

  if suma mod k <> 0 then
  begin
    writeln('-1');
  end
  else
  begin
    suma := suma div k;
    sumat := 0;

    for i := 1 to n do
    begin
      read(x);
      if sumat + x < suma then
      begin
        sumat := sumat + x;
      end
      else
      begin
        if sumat + x = suma then
        begin
          sumat := 0;
          inc(cont);
          r[cont] := i;
        end
        else
        begin
          iesit := true;
          break;
        end;
      end;
    end;

    if iesit = true then
    begin
      write('-1') ;
    end
    else
    begin
      for i := 1 to cont do
        write(r[i],' ');
    end;

  end;

  close(output);
  close(input);
end.
