open Jest;

test("addition", _ =>
  Expect.(3 + 4 |> expect |> toBe(7))
);