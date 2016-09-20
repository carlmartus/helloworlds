-- Fundamentals
n2 :: Float -> Float
n2 x = x*x

data Vec3f = Vec3f { x :: Float, y :: Float, z :: Float } deriving Show
data Triangle = Triangle { normal :: Vec3f } deriving Show

type Vec3fCombine = Vec3f -> Vec3f -> Vec3f

vec3f_compSum :: Vec3f -> Float
vec3f_compSum v = (x v) + (y v) + (z v)

vec3f_comp :: (Float -> Float) -> Vec3f -> Vec3f
vec3f_comp f v = Vec3f (f (x v)) (f (y v)) (f (z v))

vec3f_comb :: (Float -> Float -> Float) -> Vec3f -> Vec3f -> Vec3f
vec3f_comb f a b = Vec3f (f (x a) (x b)) (f (y a) (y b)) (f (z a) (z b))

vec3f_length :: Vec3f -> Float
vec3f_length = sqrt . vec3f_compSum . (vec3f_comp n2)

vec3f_normalize :: Vec3f -> Vec3f
vec3f_normalize v = vec3f_comp (* (1.0 / vec3f_length(v))) v

vec3f_cross :: Vec3f -> Vec3f -> Vec3f
vec3f_cross a b = Vec3f vx vy vz
    where
    vx = y a * z b - z a * y b
    vy = z a * x b - x a * z b
    vz = x a * y b - y a * x b

-- Geometry
pointsToTriangle :: Vec3f -> Vec3f -> Vec3f -> Triangle
pointsToTriangle a b c = Triangle normal
    where
    e0 = vec3f_comb (-) b a
    e1 = vec3f_comb (-) c a
    normal = vec3f_normalize $ vec3f_cross e0 e1

main :: IO ()
main = putStrLn "Geometry"

