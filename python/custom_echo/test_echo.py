import cecho


def test_echofail():
    echo = cecho.Cecho("")

    assert echo.echo() is False


def test_echosucceed():
    echo = cecho.Cecho("Hello There")

    assert echo.echo() is True
