type selem=record
       pos,v:longint;
     end;
var n,m,i,j,cont,bonus,l,bg,en:longint;
    w,k:array[0..2005]of longint;
    a:array[0..1005,0..2005]of int64;
    s:array[0..1005]of selem;
    ok:boolean;

procedure Modifica(x:longint);inline;
var min:longint;
begin
  bonus := 0;
  while (cont > 0) and (x > 0) do
  begin
    min := x; if min > s[cont].v then min := s[cont].v;
    x := x - min;
    bonus := bonus + min*(j-s[cont].pos);
    s[cont].v := s[cont].v-min;
    if s[cont].v = 0 then dec(cont);
  end;
  if x > 0 then ok := false else ok := true;
end;

begin
  {assign(input,'run.in'); reset(input);
  assign(output,'run.out'); rewrite(output); }

  readln(n,m);
  for i := 1 to n do read(w[i]); readln();
  for i := 1 to n do read(k[i]); readln();
  for i := n+1 to 2*n do
  begin
    w[i] := w[i-n]-k[i-n];
    k[i] := k[i-n];
    w[i-n] := w[i];
  end;

  for i := 1 to n do
  begin
    cont := 0; a[i,i] := 0;
    for j := i+1 to i+n-1 do
    begin
      ok := true;

      if w[j-1] >= 0 then
      begin
        if w[j-1] > 0 then
        begin
          inc(cont);
          s[cont].pos := j; s[cont].v := w[j-1];
        end;

        a[i,j] := a[i,j-1];
      end
      else
      begin
        Modifica(-w[j-1]);
        if ok then
          a[i,j] := a[i,j-1]+bonus
        else
        begin
          for l := j to i+n-1 do a[i,l] := -1;
          break;
        end;
      end;
      if not ok then break;
    end;

  end;

  k[0] := 0;
  for i := 1 to 2*n do k[i] := k[i] + k[i-1];

  for i := 1 to m do
  begin
    readln(bg,en);
    if en < bg then en := en + n;
    inc(en); inc(bg);

    if a[bg,en] = -1 then
      writeln(-1)
    else
      writeln(a[bg,en]+k[en-1]-k[bg-1]);
  end;


  {close(input);
  close(output); }
end.
