#define TINYOBJLOADER_IMPLEMENTATION
#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "tiny_obj_loader.h"


int main()
{
    hittable_list world;

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./";

    std::string patho = "./local/lowpoly_tree.obj";
    if (!reader.ParseFromFile(patho)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjLoader: " << reader.Error() << std::endl;
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::clog << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[0].mesh.num_face_vertices.size(); f++) {
        size_t fv = size_t(shapes[0].mesh.num_face_vertices[f]);

        point3 triangle_points[3];

        // loop over face vertices
        for (size_t v = 0; v < fv; v++) {
            // vertex access
            tinyobj::index_t idx = shapes[0].mesh.indices[index_offset + v];
            tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
            tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
            tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

            triangle_points[v] = point3(vx * 0.3, vy * 0.3 - 11, vz * 0.3 - 15);
      

            //std::clog << '(' << vx << ", " << vy << ", " << vz << ')' << std::endl;
        }

        world.add(
            make_shared<triangle>(
                triangle_points[0],
                triangle_points[1],
                triangle_points[2],
                make_shared<metal>(color(0.1, 0.9, 0.1), 0.0)
            )
        );

        index_offset += fv;
    }

    //std::cout << "model loading done." << std::endl;

	/*hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 90;
    cam.lookfrom = point3(-2, 2, 1);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 10.0;
    cam.focus_dist = 3.4;

    cam.render(world);*/


    // --------final image ---------------------------------------------------
    auto start = std::chrono::high_resolution_clock::now();

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    /*world.add(make_shared<triangle>(
        point3(-12.0, 2.0, 0.0),
        point3(-8.0, 2.0, 0.0),
        point3(-10.0, 3.5, 0.0),
        make_shared<metal>(color(0.7, 0.6, 0.5), 0.3)
    ));*/

    world.add(make_shared<triangle>(
        point3(-10.0,0.0, -4.0),
        point3(-8.0, 0.0, -2.0),
        point3(-8.0, 2.5, -4.0),
        make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)
    ));

    world.add(make_shared<triangle>(
        point3(-8.0, 0.0, -2.0),
        point3(-6.0, 0.0, -4.0),
        point3(-8.0, 2.5, -4.0),
        make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)
    ));

   /* world.add(make_shared<triangle>(
        point3(-12.0, 2.0, 0.0),
        point3(-8.0, 2.0, 0.0),
        point3(-10.0, 3.5, 0.0),
        make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)
    ));

    world.add(make_shared<triangle>(
        point3(-12.0, 2.0, 0.0),
        point3(-8.0, 2.0, 0.0),
        point3(-10.0, 3.5, 0.0),
        make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)
    ));*/



    /*for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    */

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 10;
    cam.max_depth = 50;

    cam.vfov = 40;
    cam.lookfrom = point3(3, 3, 19);
    cam.lookat = point3(1, 4, 0);
    //cam.lookfrom = point3(0, 0, 0);  //cam.lookfrom = point3(13, 2, 3);
    //cam.lookat = point3(0, 0, -10);//cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::clog << "main duration: " << duration.count() << std::endl;
}