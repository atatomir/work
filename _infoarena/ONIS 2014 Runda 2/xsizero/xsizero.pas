var bufin,bufout:array[1..65000]of byte;
    a:array[1..2,1..8]of byte;
    xu,zu:byte;
    t,i,j:longint;
    x:char;
    resp:string;
    bx,bz,plinx,plinz:byte;

procedure make_rez;
begin
  bx := 0; bz := 0;
  for i := 1 to 8 do
  begin
    if (a[1,i] =2) and (a[2,i] =0) then inc(bx) else
    if (a[2,i] =2) and (a[1,i] =0) then inc(bz);

    if a[1,i] = 3 then inc(plinx) else
    if a[2,i] = 3 then inc(plinz);
  end;
end;

begin
  assign(input,'xsizero.in'); reset(input);
  assign(output,'xsizero.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
  t := 0;

  while not eof(input) do
  begin
    for i := 1 to 2 do
      for j := 1 to 8 do a[i,j] := 0;
    xu := 0; zu := 0;  inc(t);  plinx := 0; plinz := 0;

    for i := 1 to 3 do
    begin
      for j := 1 to 3 do
      begin
        read(x);
        case x of
          'X':begin
                inc(xu);
                inc(a[1,i]);
                inc(a[1,3+j]);
                if i = j then inc(a[1,7]);
                if (i+j=4) then inc(a[1,8])
              end;
          '0':begin
                inc(zu);
                inc(a[2,i]);
                inc(a[2,3+j]);
                if i = j then inc(a[2,7]);
                if (i+j=4) then inc(a[2,8])
              end;
        end;

      end;
      readln();
    end;


    if (xu - zu >=2)or(zu - xu >=1) then
      resp := 'invalid'
    else
    begin
      make_rez;

        if xu = zu then  //daca x e la rand
        begin
          if bx >= 1 then resp := 'win' else
          if bz >= 2 then resp := 'lose' else
          resp := 'draw';
        end
        else
        begin     //daca 0 e la rand
          if bz >= 1 then resp := 'lose' else
          if bx >= 2 then resp := 'win' else
          resp := 'draw';
        end;
    end;

    if plinx >= 1 then resp := 'win' else
    if plinz >= 1 then resp := 'lose';
    if (plinx >= 1) and (plinz >= 1) then resp := 'invalid';
    if (plinx >= 1) and (xu=zu) then resp := 'invalid';
    if (plinz >= 1) and (xu>zu) then resp := 'invalid';

    writeln('Testul #',t,': ',resp);

  end;



  close(input);
  close(output);
end.
