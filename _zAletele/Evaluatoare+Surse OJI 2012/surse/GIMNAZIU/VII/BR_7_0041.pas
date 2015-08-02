program compar_moise;
var f,g:text;
    s:array[0..102000] of char;
    v:array[0..102000] of longint;
    i,n,k:longint;
    ok:boolean;
begin
  assign(f,'compar.in');reset(f);
  assign(g,'compar.out');rewrite(g);
  i:=1;
  while not eof(f) do begin
                        read(f,s[i]);
                        inc(i);
                      end;
  for n:=1 to i-1 do if (s[n]<>'<') and (s[n]<>'>') then break;
  if n=i-1 then writeln(g,n+1)
           else writeln(g,n);
  if n=i-1 then inc(n);
  for i:=1 to n do v[i]:=0;
  k:=1;
  while k<=n do
    begin
      i:=1;
      if ((s[1]='<') and (v[1]=0)) or ((s[1]='>') and (v[2]<>0) and (v[1]=0))
                                 then begin
                                        v[i]:=k;
                                        ok:=true;
                                      end
                                 else
                   begin
                     i:=2; ok:=false;
                     while (i<n) and (ok=false) do
                       begin
                         if v[i]=0 then
                           begin
                             if (v[i-1]=0) and (v[i+1]=0) then
                               if (s[i-1]='>') and (s[i]='<')
                                  then v[i]:=k;
                             if (v[i-1]<>0) and (v[i+1]=0) then
                               if (s[i]='<') and (s[i-1]='<')
                                  then v[i]:=k;
                             if (v[i-1]=0) and (v[i+1]<>0) then
                               if (s[i]='>') and (s[i-1]='>')
                                  then v[i]:=k;
                             if (v[i-1]<>0) and (v[i+1]<>0) then
                               if (s[i-1]='<') and (s[i]='>')
                                  then v[i]:=k;
                             if v[i]=k then ok:=true;
                           end;
                         inc(i);
                       end;
                   end;
      if (ok=false) and (v[n]=0) then begin
                                       v[n]:=k;
                                       ok:=false;
                                     end;
      if (ok=false) and (v[n]<>0) and (s[1]='<') then if v[1]=0 then v[1]:=k;
      if k=n then for i:=1 to n do if v[i]=0 then begin
                                                    v[i]:=k;
                                                    break;
                                                  end;
      inc(k);
    end;
  for i:=1 to n do write(g,v[i],' ');
  close(f); close(g);
end.
