program unific_moise;
var f,g:text;
    v:array[0..102000] of qword;
    a,b,tot:array[0..50] of longint;
    v1,v2:array[0..50] of longint;
    ok,cif,zer,sters:boolean;
    i,n,j,c1,c2,l,o,c,max,cifra:longint;
    x,y,nr:qword;
begin
  assign(f,'unific.in');reset(f);
  assign(g,'unific.out');rewrite(g);
  readln(f,n);
  for i:=1 to n do readln(f,v[i]);
  ok:=true;
  while ok=true do
    begin
      ok:=false;
      for i:=1 to n-1 do
        begin
          cif:=false;
          x:=v[i]; y:=v[i+1];
          c1:=0; c2:=0;
          while x<>0 do begin
                          inc(a[x mod 10]);
                          inc(tot[x mod 10]);
                          inc(c1);
                          v1[c1]:=x mod 10;
                          x:=x div 10;
                        end;
          while y<>0 do begin
                          inc(b[y mod 10]);
                          inc(tot[y mod 10]);
                          inc(c2);
                          v2[c2]:=y mod 10;
                          y:=y div 10;
                        end;
          cif:=false;
          for j:=0 to 9 do if (a[j]>0) and (b[j]>0) then cif:=true;
          if cif=true then
            begin
              for j:=0 to 9 do
                if (a[j]>0) and (b[j]>0) then
                  begin
                    sters:=true;
                    while sters=true do
                      begin
                        sters:=false;
                        for l:=1 to c1 do
                          if v1[l]=j then begin
                                            for o:=l to c1-1 do v1[o]:=v1[o+1];
                                            v1[c1]:=0;
                                            dec(c1);
                                            sters:=true;
                                            break;
                                          end;
                      end;
                    sters:=true;
                    while sters=true do
                      begin
                        sters:=false;
                        for l:=1 to c2 do
                          if v2[l]=j then begin
                                            for o:=l to c2-1 do v2[o]:=v2[o+1];
                                            v2[c2]:=0;
                                            dec(c2);
                                            sters:=true;
                                            break;
                                          end;
                      end;
                  end;
              for j:=c2+1 to c2+c1 do v2[j]:=v1[j-c2];
              nr:=0;
              c:=c1+c2;
              for j:=c downto 1 do nr:=nr*10+v2[j];
              if c>0 then begin
                            v[i]:=nr;
                            for j:=i+1 to n-1 do v[j]:=v[j+1];
                            v[n]:=0;
                            dec(n);
                          end;
              if c=0 then begin
                            v[i]:=0;
                            v[i+1]:=0;
                            for j:=i to n-1 do v[j]:=v[j+1];
                            v[n]:=0;
                            dec(n);
                            for j:=i to n-1 do v[j]:=v[j+1];
                            v[n]:=0;
                            dec(n);
                          end;
            end;
          for j:=0 to 9 do begin
                             a[j]:=0;
                             b[j]:=0;
                           end;
          for j:=0 to 4 do begin
                              v1[j]:=0;
                              v2[j]:=0;
                            end;
          if cif=true then begin
                             ok:=true;
                             break;
                           end;
        end;
    end;
  max:=-1; cifra:=0;
  for i:=0 to 9 do if tot[i]>max then begin
                                        max:=tot[i];
                                        cifra:=i;
                                      end;
  writeln(g,cifra);
  if n>0 then begin
                writeln(g,n);
                for i:=1 to n do write(g,v[i],' ');
              end;
  close(f); close(g);
end.
