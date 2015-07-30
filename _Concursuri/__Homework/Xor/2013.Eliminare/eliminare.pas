var bufin,bufout:array[1..65000]of byte;
    a:array[1..100001]of longint;
    n,q,t,i:longint;
    ok:boolean;
    x,loc:longint;

procedure binara(x:longint;var ok:boolean;var loc:longint);
var u,v,m:longint;
begin
  u := 1 ; v := n;  ok := false;
  repeat
    //writeln('!',u,'!',v,'!',x);

    m := ((v-u) div 2) +  u;
    if x = a[m] then
    begin
      ok := true;
      u := v+10;
    end
    else
    begin
      if x < a[m] then
      begin
        v := m-1;
      end
      else
      begin
        u := m +1;
      end;
    end;

  until u > v;

  loc := v;

  //writeln('?',u,'?',v,'?',loc);

end;


begin
  assign(input,'eliminare.in'); reset(input);
  assign(output,'eliminare.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
  readln(n,q);
  for i := 1 to n do read(a[i]);

  repeat
    ok := false;
    for i := 1 to n-1 do
      if a[i] > a[i+1] then
      begin
        ok := true;
        t := a[i];
        a[i]:= a[i+1];
        a[i+1] := t;
      end;
  until ok = false;

  for i := 1 to q do
  begin
    readln(x);
    binara(x,ok,loc);
    if ok = true then
      writeln('0')
    else
    begin
      writeln(x-loc);
    end;
  end;


  close(input);
  close(output);
end.
