# examples/server_simple.py
from aiohttp import web
import jinja2
import aiohttp_jinja2
import os


routes = web.RouteTableDef()


@routes.get('/')
@routes.get('/index')
async def get_index_page(request: web.Request) -> web.Response:

    context = {
        'car_ip': '',
        'camera_ip': ''
    }
    response = aiohttp_jinja2.render_template("base.html", request,
                                              context=context)

    return response


@routes.post('/')
@routes.post('/index')
async def connect_to_car(request: web.Request) -> None:
    car_ip = ''
    camera_ip = ''
    
    if request.body_exists:
        data = await request.text()
        _, car_ip, _, camera_ip = data.replace('&', '=').split('=')
    
    context = {
        'car_ip': car_ip,
        'camera_ip': camera_ip
    }
    response = aiohttp_jinja2.render_template("base.html", request,
                                              context=context)

    return response


app = web.Application()

aiohttp_jinja2.setup(
    app, loader=jinja2.FileSystemLoader(os.path.join(os.getcwd(), "templates"))
)

app.add_routes(routes)
app.router.add_static('/static', './static')

if __name__ == '__main__':
    web.run_app(app)
