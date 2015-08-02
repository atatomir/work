program cautare_binara;
var n,x,i,u,v,m:longint;
    bufin:array[1..65000]of byte;
    a:array[1..1000000]of longint;
    ok :boolean;

begin
  assign(input,'binara.in'); reset(input);
  assign(output,'binara.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,x);
  for i := 1 to n do read(a[i]);
  u := 1; v := n ; ok := false;

  repeat
    m := ((v-u)div 2)+ u;
    if a[m] = x then
    begin
      writeln('Elementul nr: ',m); ok := true;
      break;
    end
    else
    begin
      if a[m] < x then
      begin
        u := m+1;
      end
      else
      begin
        v := m-1 ;
      end;
    end;

   writeln(u,' ',v);
  until u > v;

  if ok = false then
  begin
    writeln('Elementul cautat nu exista in sir!');
    writeln('Pozitii: ',v,'-',u);
  end;

  close(input); close(output);
end.
