program arrows;
var f,g:text;
    a,b,c:array[0..550,0..550] of integer;
    t,n,m,i,j,lin,col,poz1,poz2,nr,ok,s,max:longint;
begin
  assign(f,'arrows.in');reset(f);
  assign(g,'arrows.out');rewrite(g);
  readln(f,t);
  readln(f,n,m);
  for i:=1 to n do
    begin
      for j:=1 to m do read(f,a[i,j]);
      readln(f);
    end;
  readln(f,lin,col);
  if t=1 then
    begin
      b[lin,col]:=1;
      ok:=0; nr:=1;
      poz1:=lin; poz2:=col;
      while ok=0 do
        begin
          case a[poz1,poz2] of
            1:inc(poz2);
            2:dec(poz1);
            3:dec(poz2);
            4:inc(poz1);
          end;
          if (poz1<1) or (poz1>n) or (poz2<1) or (poz2>m) then ok:=2;
          if ok=0 then if b[poz1,poz2]=1 then ok:=1;
          if ok=0 then if b[poz1,poz2]=0 then begin
                                                b[poz1,poz2]:=1;
                                                inc(nr);
                                              end;
        end;
      if ok=1 then nr:=nr*1000;
      writeln(g,nr);
    end;
  if t=2 then
    begin
      for lin:=1 to n do
        for col:=1 to m do if c[lin,col]=0 then
          begin
            for i:=1 to n do
              for j:=1 to m do b[i,j]:=0;
            b[lin,col]:=1;
            ok:=0; nr:=1;
            poz1:=lin; poz2:=col;
            if c[poz1,poz2]=0 then
            while ok=0 do
              begin
                case a[poz1,poz2] of
                  1:inc(poz2);
                  2:dec(poz1);
                  3:dec(poz2);
                  4:inc(poz1);
                end;
                if c[poz1,poz2]=1 then begin
                                         ok:=3;
                                         break;
                                       end;
                if (poz1<1) or (poz1>n) or (poz2<1) or (poz2>m) then ok:=2;
                if ok=0 then if b[poz1,poz2]=1 then ok:=1;
                if ok=0 then if b[poz1,poz2]=0 then b[poz1,poz2]:=1;
              end;
            if ok=3 then c[lin,col]:=1;
            if ok=1 then
              begin
                c[lin,col]:=1;
                for i:=1 to n do
                  for j:=1 to m do if b[i,j]=1 then c[i,j]:=1;
              end;
          end;
      s:=0;
      for i:=1 to n do
        for j:=1 to m do s:=s+c[i,j];
      writeln(g,s);
    end;
  if t=3 then
    begin
      max:=0;
      for lin:=1 to n do
        for col:=1 to n do
      begin
        for i:=1 to n do
          for j:=1 to m do b[i,j]:=0;
        b[lin,col]:=1;
        ok:=0; nr:=1;
        poz1:=lin; poz2:=col;
        while ok=0 do
          begin
            case a[poz1,poz2] of
              1:inc(poz2);
              2:dec(poz1);
              3:dec(poz2);
              4:inc(poz1);
            end;
            if (poz1<1) or (poz1>n) or (poz2<1) or (poz2>m) then ok:=2;
            if ok=0 then if b[poz1,poz2]=1 then ok:=1;
            if ok=0 then if b[poz1,poz2]=0 then begin
                                                  b[poz1,poz2]:=1;
                                                  inc(nr);
                                                end;
          end;
        if ok=1 then nr:=nr*1000;
        if nr>max then max:=nr;
      end;
      writeln(g,max);
    end;
  close(f); close(g);
end.
