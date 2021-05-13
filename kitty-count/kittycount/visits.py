from flask import (
    Blueprint, abort, flash, g, redirect, render_template, request, url_for
)

from datetime import datetime

from kittycount.db import get_db

bp = Blueprint('visits', __name__)

@bp.route('/')
def index():
    db = get_db()
    visits = db.execute(
        """
        SELECT visits, datetime(time, 'localtime') as time
        FROM visits
        ORDER BY time DESC
        """
    ).fetchall()
    return render_template('visits/visits.html', visits=visits)

@bp.route('/webhook', methods=['POST'])
def webhook():
    db = get_db()
    if request.method == 'POST':
        print(request.json)
        visits = request.json['count']
        db.execute(
                'INSERT INTO visits (visits)'
                ' VALUES (?)',
                (visits,)
            )
        db.commit()
        return redirect(url_for('visits.index'))

@bp.context_processor
def utility_processor():
    def str2dt(s):
        return datetime.strptime(s, "%Y-%m-%d %H:%M:%S")
    return dict(str2dt=str2dt)