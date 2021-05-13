import os

from flask import Flask

def create_app(test_config=None):
    app = Flask(__name__, instance_relative_config=True)
    app.config.from_mapping(
        SECRET_KEY= 'dev',
        DATABASE=os.path.join(app.instance_path, 'kittycount.sqlite'),
    )

    if test_config is None:
        app.config.from_pyfile('config.py', silent=True)
    else:
        app.config.from_mapping(test_config)

    try:
        os.makedirs(app.instance_path)
    except OSError:
        pass

    from . import visits
    app.register_blueprint(visits.bp)

    from . import db
    db.init_app(app)

    return app

app = create_app()