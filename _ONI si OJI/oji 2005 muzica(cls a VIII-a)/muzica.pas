type inregistrare=record
       pos:longint;
       aj:boolean;
     end;
var a,b,i,h,pos,j:longint;
    v:array[0..1010]of inregistrare;
    c:array[0..5000]of byte;
    iesi:boolean;

begin
  assign(input,'muzica.in'); reset(input);
  assign(output,'muzica.out'); rewrite(output);

  readln(a,b);
  for i := 0 to b+1 do v[i].aj := false;

  iesi := false; i := 0;
  repeat
    inc(i);

    if v[a].aj = false then
    begin
      v[a].aj := true;
      v[a].pos := i;

      c[i] := a*10 div b;
      a := a*10 mod b;
    end
    else
    begin
      iesi := true;
      pos := v[a].pos;
      i := i-1;
    end;

  until iesi = true;

  for j := 1 to i do write(c[j]);
  writeln(' ',i-pos+1);


  close(input);
  close(output);
end.
