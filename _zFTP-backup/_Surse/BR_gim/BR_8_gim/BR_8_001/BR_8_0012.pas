program tcif;
var f,g:text;
    v,nr:array[0..1100] of longint;
    z,cif:array[0..10] of longint;
    a,b,c,c1,c2,c3,n,min,m,i,j,s,ci,poz,aux:longint;
    x:char;
    inv,ok,minim:boolean;
begin
  assign(f,'tcif.in');reset(f);
  assign(g,'tcif.out');rewrite(g);
  readln(f,a,b,c,c1,c2,c3);
  i:=1;
  while not eof(f) do
    begin
      read(f,x);
      if (ord(x)>=ord('0')) and (ord(x)<=ord('9')) then
        begin
          v[i]:=ord(x)-ord('0');
          inc(i);
        end;
    end;
  dec(i);
  n:=i;
  s:=a+b+c;
  if s>n then
    begin
      z[1]:=a; z[2]:=b; z[3]:=c;
      cif[1]:=c1; cif[2]:=c2; cif[3]:=c3;
      min:=10;
      for i:=1 to 3 do if min>cif[i] then min:=cif[i];
      if min=0 then
        begin
          ci:=10;
          for i:=1 to 3 do if cif[i]<>0 then if ci>cif[i] then ci:=cif[i];
          write(g,ci);
          if ci=cif[1] then dec(z[1]);
          if ci=cif[2] then dec(z[2]);
          if ci=cif[3] then dec(z[3]);
        end;
      repeat
        inv:=false;
        for i:=1 to 2 do if cif[i]>cif[i+1] then
          begin
            m:=z[i]; z[i]:=z[i+1]; z[i+1]:=m;
            m:=cif[i]; cif[i]:=cif[i+1]; cif[i+1]:=m;
            inv:=true;
          end;
      until not inv;
      for i:=1 to 3 do
        for j:=1 to z[i] do write(g,cif[i]);
    end;
  if s=n then
    begin
      z[1]:=a; z[2]:=b; z[3]:=c;
      cif[1]:=c1; cif[2]:=c2; cif[3]:=c3;
      repeat
        inv:=false;
        for i:=1 to 2 do if cif[i]>cif[i+1] then
          begin
            m:=z[i]; z[i]:=z[i+1]; z[i+1]:=m;
            m:=cif[i]; cif[i]:=cif[i+1]; cif[i+1]:=m;
            inv:=true;
          end;
      until not inv;
      for i:=1 to n do nr[i]:=0;
      minim:=false;
      for i:=1 to n do
        begin
          ok:=false;
          for j:=1 to 3 do if cif[j]=v[i] then
            if z[j]>0 then begin
                             nr[i]:=cif[j];
                             dec(z[j]);
                             ok:=true;
                             break;
                           end;
          if ok=false then
            begin
              for j:=1 to 3 do if (cif[j]>v[i]) and (z[j]>0) then
                begin
                  nr[i]:=cif[j];
                  dec(z[j]);
                  ok:=true;
                  break;
                end;
              if ok=false then for j:=i-1 downto 1 do if nr[j]<cif[3]
                then begin
                       if ok=false then
                        if (nr[j]=cif[1]) and (z[2]>0) then
                                            begin
                                              nr[j]:=cif[2];
                                              inc(z[1]); dec(z[2]);
                                              ok:=true;
                                            end;
                       if ok=false then
                        if (nr[j]=cif[1]) and (z[2]=0) and (z[3]>0) then
                                            begin
                                              nr[j]:=cif[3];
                                              inc(z[1]); dec(z[3]);
                                              ok:=true;
                                            end;
                       if ok=false then
                        if (nr[j]=cif[2]) and (z[3]>0) then
                                            begin
                                              nr[j]:=cif[3];
                                              inc(z[2]); dec(z[3]);
                                              ok:=true;
                                            end;
                       if ok=true then break;
                       if ok=false then begin
                                          if nr[j]=cif[1] then inc(z[1]);
                                          if nr[j]=cif[2] then inc(z[2]);
                                          if nr[j]=cif[3] then inc(z[3]);
                                          nr[j]:=0;
                                        end;
                     end
                else begin
                       if nr[j]=cif[1] then inc(z[1]);
                       if nr[j]=cif[2] then inc(z[2]);
                       if nr[j]=cif[3] then inc(z[3]);
                       nr[j]:=0;
                     end;

            end;
          for j:=1 to i do if nr[j]>v[j] then
            begin
              poz:=j;
              minim:=true;
              break;
            end;
          if minim=true then break;
        end;
      if minim=false then
        begin
          aux:=nr[n];
          nr[n]:=nr[n-1];
          nr[n-1]:=aux;
          poz:=n;
        end;
      for i:=poz+1 to n do nr[i]:=0;
      for i:=1 to poz do write(g,nr[i]);
      for i:=poz+1 to n do
        begin
          if z[3]>0 then nr[i]:=cif[3];
          if z[2]>0 then nr[i]:=cif[2];
          if z[1]>0 then nr[i]:=cif[1];
          if nr[i]=cif[1] then dec(z[1]);
          if nr[i]=cif[2] then dec(z[2]);
          if nr[i]=cif[3] then dec(z[3]);
        end;
      for i:=poz+1 to n do write(g,nr[i]);
    end;
  close(f); close(g);
end.