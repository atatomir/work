var l,h,ll,vol,arie,hf:real;
    i,n,cubnr:longint;

begin
  assign(input,'cuburi.in'); reset(input);
  assign(output,'cuburi.out'); rewrite(output);

  readln(l,n,h); ll := l;

  vol := 0; arie := 0; hf := 0; cubnr := 0;

  for i := 1 to n do
  begin
    vol := vol + ll*ll*ll;
    arie := arie + ll*ll*4.5;
    if i = 1 then arie := arie + ll*ll;
    if i = n then arie := arie + (ll*ll)/2;
    hf := hf + ll;

    if cubnr = 0 then
      if hf > h then
        cubnr := i;


    ll := (ll*sqrt(2))/2;
  end;

  writeln(vol:0:5);
  writeln(arie:0:5);
  writeln(hf:0:5);

  if cubnr = 0 then
  begin
    cubnr := -1;
    for i := n+1 to 3000 do
    begin
      hf := hf + ll;

      if hf > h then
      begin
        cubnr := i;
        break;
      end;

      ll := (ll*sqrt(2))/2;
    end;
  end;

  writeln(cubnr);


  close(input);
  close(output);
end.
