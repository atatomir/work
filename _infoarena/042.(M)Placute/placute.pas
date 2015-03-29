var n,i,t:longint;
    k:word;
    g:array[1..100000]of longint;
    c:array[1..100000]of word;
    greu:int64;
    int,ant:longint;
    bufin:array[1..65000]of byte;
    ok:boolean;

begin
  assign(input,'placute.in'); reset(input);
  assign(output,'placute.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  for i := 1 to n do
  begin
    readln(g[i],c[i]);
  end;

  repeat
    ok := true;
    for i := 1 to n-1 do
    begin
      if g[i] < g[i+1] then
      begin
        t := g[i];
        g[i] := g[i+1];
        g[i+1] := t;

        t := c[i];
        c[i] := c[i+1];
        c[i+1] := t;
        ok := false;
      end;
    end;
  until ok = true;

  greu := g[1]; i := 1; int :=0; ant := c[1];
  repeat
    //writeln(i);
    if int <> 0 then
    begin
      i := int -1;
      int := 0
    end;
    inc(i);
    if (c[i] <> ant) and (g[i] <> 0) then
    begin
      greu := greu + g[i];   //writeln(g[i],'-',c[i],'-@',ant);
      g[i] := 0;
      ant := c[i];
      int := 0;
    end
    else
    begin
      if (c[i] = ant) and (g[i] <> 0) then
      begin
        if int = 0 then int := i;
      end;
      inc(i); ok := false;
      while (i<=n) and (ok=false) do
      begin
        if (c[i] <> ant) and (g[i] <> 0) then
          ok := true
        else
          inc(i);

      end;
      if ok = true then
      begin
        greu := greu + g[i];     //writeln(g[i],'-',c[i],'-',ant);
        g[i] := 0;
        ant := g[i];
      end
      else
      begin
        i := n;
        int := 0;
      end;
    end;

    //writeln(i,'!',n,' ',int);
  until (i>=n) and (int = 0);

  write(greu);

  close(input);
  close(output);
end.
